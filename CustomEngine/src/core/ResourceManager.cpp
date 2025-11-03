#include "core/ResourceManager.hpp"
#include <raylib.h>

ResourceManager &ResourceManager::GetInstance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::LoadTextureFromPath(std::string path) {

  auto it = textures.find(path);
  if (it != textures.end()) {
    it->second.refCount++;
    return;
  }
  TextureResource texture;
  texture.texture = LoadTexture(path.c_str());
  texture.refCount = 1;
  if (texture.texture.id != 0) {
    textures[path] = texture;
  }
}

void ResourceManager::UnloadTextureFromPath(std::string path) {
  auto it = textures.find(path);
  if (it == textures.end())
    return;
  it->second.refCount--;
  if (it->second.refCount <= 0) {
    UnloadTexture(it->second.texture);
    textures.erase(it);
  }
}

Texture2D *ResourceManager::GetTexture(std::string path) {
  auto it = textures.find(path);
  if (it != textures.end())
    return &it->second.texture;
  else
    return nullptr;
}

void ResourceManager::UnloadAll() {
  for (auto &[_, textureRes] : textures) {
    UnloadTexture(textureRes.texture);
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
