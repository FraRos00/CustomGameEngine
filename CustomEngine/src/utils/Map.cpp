#include "utils/Map.hpp"
#include "core/ResourceManager.hpp"
#include "globals/globals.hpp"
#include <fstream>
#include <string>

bool Map::Load(const std::string &jsonPath) {
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
  // Costruisci mappa di collisioni per i tile
  ParseTilesetCollisions(mapData["tilesets"][0]);

  // Costruisci i rettangoli di collisione nel mondo
  BuildMapCollisions();

  return true;
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
