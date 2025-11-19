#include "utils/Map.hpp"
#include "core/ResourceManager.hpp"
#include "globals/globals.hpp"
#include <filesystem>
#include <fstream>
#include <string>

bool Map::LoadMapTexture(const std::string &jsonPath) {
  std::filesystem::path p(jsonPath);
  mapName = p.stem().string();
  std::ifstream f(jsonPath);
  if (!f.is_open()) {
    TraceLog(LOG_ERROR, "Cannot open map file: %s", jsonPath.c_str());
    return false;
  }
  f >> mapData;

  tileWidth = mapData["tilewidth"];
  tileHeight = mapData["tileheight"];
  mapWidth = mapData["width"];
  mapHeight = mapData["height"];

  // Carica tileset
  std::string imagePath = mapData["tilesets"][0]["image"];
  fullPath = "maps/" + imagePath;
  ResourceManager::GetInstance().LoadTextureFromPath(fullPath);
  tileset = ResourceManager::GetInstance().GetTexture(fullPath);
  if (!tileset) {
    TraceLog(LOG_ERROR, "Cannot load tileset texture: %s", fullPath.c_str());
    return false;
  }

  return true;
}

void Map::ParseMapData() {
  // Costruisci mappa di collisioni per i tile
  ParseTilesetCollisions(mapData["tilesets"][0]);

  // Costruisci i rettangoli di collisione nel mondo
  BuildMapCollisions();

  // Trova il punto di spawn del giocatore
  ParseSpawnPoint();

  // Trova le zone di teletrasporto
  ParseTeleportZones();
}

void Map::ParseSpawnPoint() {
  for (auto &layer : mapData["layers"]) {
    if (layer["type"] == "objectgroup" && layer["name"] == "spawn") {
      for (auto &obj : layer["objects"]) {
        if (obj["name"] == "player_spawn") {
          spawnPoint = {obj["x"], obj["y"]};
          return;
        }
      }
    }
  }
  spawnPoint = {0, 0};
}

void Map::ParseTeleportZones() {
  for (auto &layer : mapData["layers"]) {
    if (layer["type"] == "objectgroup" && layer["name"] == "spawn") {
      for (auto &obj : layer["objects"]) {
        if (obj["type"] == "teleport") {
          TeleportZone z;
          z.rect.x = obj["x"];
          z.rect.y = obj["y"];
          z.rect.width = obj["width"];
          z.rect.height = obj["height"];
          for (auto &prop : obj["properties"]) {
            if (prop["name"] == "side") {
              z.side = prop["value"];
            }
          }
          teleportZones[obj["name"]] = z;
        }
      }
    }
  }
}

void Map::Unload() {
  ResourceManager::GetInstance().UnloadTextureFromPath(fullPath);
  tileset = nullptr;
  collisions.clear();
  tileCollisionMap.clear();
}

void Map::ParseTilesetCollisions(const json &tilesetData) {
  int firstGid = tilesetData["firstgid"];

  if (!tilesetData.contains("tiles"))
    return;

  for (auto &tile : tilesetData["tiles"]) {
    int id = tile["id"];
    std::vector<Rectangle> rects;

    if (tile.contains("objectgroup")) {
      for (auto &obj : tile["objectgroup"]["objects"]) {
        Rectangle r;
        r.x = (float)obj["x"];
        r.y = (float)obj["y"];
        r.width = (float)obj["width"];
        r.height = (float)obj["height"];
        rects.push_back(r);
      }
    }
    tileCollisionMap[firstGid + id] = rects;
  }
}

void Map::BuildMapCollisions() {
  collisions.clear();

  for (auto &layer : mapData["layers"]) {
    if (layer["type"] == "tilelayer") {
      int width = layer["width"];
      const auto &data = layer["data"];

      for (int i = 0; i < (int)data.size(); i++) {
        int gid = data[i];
        if (gid == 0)
          continue;

        int x = (i % width);
        int y = (i / width);

        if (tileCollisionMap.count(gid)) {
          for (auto &r : tileCollisionMap[gid]) {
            CollisionShape c;
            c.rect.x = x * tileWidth + r.x;
            c.rect.y = y * tileHeight + r.y;
            c.rect.width = r.width;
            c.rect.height = r.height;
            collisions.push_back(c);
          }
        }
      }
    }
  }
}

void Map::Draw() const {
  for (auto &layer : mapData["layers"]) {
    if (layer["type"] != "tilelayer")
      continue;

    int width = layer["width"];
    int height = layer["height"];
    const auto &data = layer["data"];

    int tilesetCols = tileset->width / tileWidth;

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int tileIndex = data[y * width + x];
        if (tileIndex == 0)
          continue;

        int tx = (tileIndex - 1) % tilesetCols;
        int ty = (tileIndex - 1) / tilesetCols;

        Rectangle src = {(float)tx * tileWidth, (float)ty * tileHeight,
                         (float)tileWidth, (float)tileHeight};
        Vector2 dest = {(float)x * tileWidth, (float)y * tileHeight};
        DrawTextureRec(*tileset, src, dest, WHITE);
      }
    }
  }
  if (global::DEBUG)
    for (auto &c : collisions) {
      DrawRectangleLines(c.rect.x, c.rect.y, c.rect.width, c.rect.height, RED);
    }
}

void Map::Draw(std::string toDrawlayer) const {
  for (auto &layer : mapData["layers"]) {
    if (layer["type"] != "tilelayer" || layer["name"] != toDrawlayer)
      continue;

    int width = layer["width"];
    int height = layer["height"];
    const auto &data = layer["data"];

    int tilesetCols = tileset->width / tileWidth;

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int tileIndex = data[y * width + x];
        if (tileIndex == 0)
          continue;

        int tx = (tileIndex - 1) % tilesetCols;
        int ty = (tileIndex - 1) / tilesetCols;

        Rectangle src = {(float)tx * tileWidth, (float)ty * tileHeight,
                         (float)tileWidth, (float)tileHeight};
        Vector2 dest = {(float)x * tileWidth, (float)y * tileHeight};
        DrawTextureRec(*tileset, src, dest, WHITE);
      }
    }
  }

  if (global::DEBUG)
    for (auto &c : collisions) {
      DrawRectangleLines(c.rect.x, c.rect.y, c.rect.width, c.rect.height, RED);
    }
}

bool Map::CheckCollision(const Rectangle &rect) const {
  for (auto &c : collisions) {
    if (CheckCollisionRecs(rect, c.rect))
      return true;
  }
  return false;
}

std::string Map::CheckTeleport(const Rectangle &rect) const {
  for (auto &pair : teleportZones) {
    if (CheckCollisionRecs(rect, pair.second.rect))
      return pair.first;
  }
  return "";
}

Vector2 Map::GetTeleportZoneRect(const std::string &zoneName) const {
  // PrintMapTeleportZones();
  auto it = teleportZones.find(zoneName);
  if (it != teleportZones.end()) {
    int offsetX = 0;
    int offsetY = 0;
    if (it->second.side == "left")
      offsetX = 1;
    if (it->second.side == "top")
      offsetY = 1;
    if (it->second.side == "right")
      offsetX = -1;
    if (it->second.side == "bottom")
      offsetY = -1;

    return {it->second.rect.x + it->second.rect.width / 2.0f + 30.0f * offsetX,
            it->second.rect.y + it->second.rect.height / 2.0f +
                30.0f * offsetY};
  }
  return spawnPoint;
}

void Map::PrintMapTeleportZones() const {
  for (const auto &pair : teleportZones) {
    TraceLog(LOG_INFO, "Teleport Zone: %s at (%.2f, %.2f, %.2f, %.2f)",
             pair.first.c_str(), pair.second.rect.x, pair.second.rect.y,
             pair.second.rect.width, pair.second.rect.height);
  }
}
