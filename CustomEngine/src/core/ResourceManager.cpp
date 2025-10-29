#include "core/ResourceManager.hpp"
#include <raylib.h>

ResourceManager &ResourceManager::GetInstance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::LoadTextureFromPath(std::string path) {
  Texture2D texture = LoadTexture(path.c_str());
  if (texture.id != 0) {
    textures[path] = texture;
  }
}

Texture2D *ResourceManager::GetTexture(std::string path) {
  auto it = textures.find(path);
  if (it != textures.end())
    return &it->second;
  else
    return nullptr;
}

void ResourceManager::UnloadAll() {
  for (auto &[_, texture] : textures) {
    UnloadTexture(texture);
  }
  textures.clear();

  for (auto &[_, font] : fonts) {
    UnloadFont(font);
  }
  fonts.clear();

  for (auto &[_, sound] : sounds) {
    UnloadSound(sound);
  }
  sounds.clear();
}
