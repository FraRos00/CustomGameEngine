#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>
class ResourceManager {

public:
  static ResourceManager &GetInstance();
  void LoadTextureFromPath(std::string path);
  Texture2D *GetTexture(std::string path);
  void LoadFont(std::string path);
  void GetFont(std::string id);
  void LoadSound(std::string path);
  void GetSound(std::string id);

  void UnloadAll();

private:
  ResourceManager() = default;
  ~ResourceManager() { UnloadAll(); }
  ResourceManager(const ResourceManager &) = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;

  std::unordered_map<std::string, Texture2D> textures;
  std::unordered_map<std::string, Font> fonts;
  std::unordered_map<std::string, Sound> sounds;
};
