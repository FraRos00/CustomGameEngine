#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>

struct TextureResource {
  Texture2D texture;
  int refCount;
};

class ResourceManager {

public:
  static ResourceManager &GetInstance();
  void LoadTextureFromPath(std::string path);
  void UnloadTextureFromPath(std::string path);
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

  std::unordered_map<std::string, std::unique_ptr<TextureResource>> textures;
  std::unordered_map<std::string, std::unique_ptr<Font>> fonts;
  std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
};
