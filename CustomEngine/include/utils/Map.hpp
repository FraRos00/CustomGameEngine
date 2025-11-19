#pragma once
#include "utils/json.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;

struct CollisionShape {
  Rectangle rect;
};

struct TeleportZone {
  Rectangle rect;
  std::string side;
};

class Map {
public:
  Map() = default;
  ~Map() { Unload(); }

  int GetWidth() const { return mapWidth * tileWidth; };
  int GetHeight() const { return mapHeight * tileHeight; };
  Vector2 GetSpawnPoint() const { return spawnPoint; };

  bool LoadMapTexture(const std::string &jsonPath);
  void ParseMapData();
  void Unload();
  void Draw() const;
  void Draw(std::string layer) const;
  bool CheckCollision(const Rectangle &rect) const;
  std::string CheckTeleport(const Rectangle &rect) const;
  Vector2 GetTeleportZoneRect(const std::string &zoneName) const;
  std::string GetMapName() const { return mapName; };

private:
  std::string mapName;
  json mapData;
  std::string fullPath;
  Vector2 spawnPoint;
  Texture2D *tileset = nullptr;
  int tileWidth = 0, tileHeight = 0;
  int mapWidth = 0, mapHeight = 0;
  std::unordered_map<int, std::vector<Rectangle>> tileCollisionMap;
  std::vector<CollisionShape> collisions;
  std::unordered_map<std::string, TeleportZone> teleportZones;

  void ParseTilesetCollisions(const json &tileset);
  void BuildMapCollisions();
  void ParseSpawnPoint();
  void ParseTeleportZones();

  void PrintMapTeleportZones() const;
};
