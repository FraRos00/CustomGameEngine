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

class Map {
public:
  Map() = default;
  ~Map() { Unload(); }

  int GetWidth() const { return mapWidth * tileWidth; };
  int GetHeight() const { return mapHeight * tileHeight; };

  bool Load(const std::string &jsonPath);
  void Unload();
  void Draw() const;
  void Draw(std::string layer) const;
  bool CheckCollision(const Rectangle &rect) const;
  Vector2 ParseSpawnPoint();

private:
  json mapData;
  std::string fullPath;
  Texture2D *tileset = nullptr;
  int tileWidth = 0, tileHeight = 0;
  int mapWidth = 0, mapHeight = 0;
  std::unordered_map<int, std::vector<Rectangle>> tileCollisionMap;
  std::vector<CollisionShape> collisions;

  void ParseTilesetCollisions(const json &tileset);
  void BuildMapCollisions();
};
