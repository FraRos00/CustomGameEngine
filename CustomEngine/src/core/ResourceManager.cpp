#include "core/ResourceManager.hpp"
#include <iostream>
<<<<<<< HEAD
=======
#include <memory>
    >>>>>>> dev
#include <raylib.h>

    ResourceManager &ResourceManager::GetInstance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::LoadTextureFromPath(std::string path) {

  auto it = textures.find(path);
  if (it != textures.end()) {
    it->second->refCount++;
    //   std::cout<<"Resource "<<path<<" already present. Incrementing
    //   refcount...\n";
    return;
  }
  auto texture = std::make_unique<TextureResource>();
  // std::cout<<"Loading Resource "<<path<<"...\n";
  texture->texture = LoadTexture(path.c_str());
  texture->refCount = 1;
  if (texture->texture.id != 0) {
    textures[path] = std::move(texture);
  }
}

void ResourceManager::UnloadTextureFromPath(std::string path) {
  auto it = textures.find(path);
  if (it == textures.end())
    return;
  it->second->refCount--;
  // std::cout<<"Reducing refcount for Resource "<<path<<"...\n";
  if (it->second->refCount <= 0) {
    // std::cout<<"Unloading Resource "<<path<<"...\n";
    UnloadTexture(it->second->texture);
    textures.erase(it);
  }
}

Texture2D *ResourceManager::GetTexture(std::string path) {
  auto it = textures.find(path);
  if (it != textures.end())
    return &it->second->texture;
  else
    return nullptr;
}

void ResourceManager::UnloadAll() {
  // std::cout<<"Unloading All Resources...\n";
  for (auto &[_, textureRes] : textures) {
    UnloadTexture(textureRes->texture);
  }
  textures.clear();

  for (auto &[_, font] : fonts) {
    UnloadFont(*font);
  }
  fonts.clear();

  for (auto &[_, sound] : sounds) {
    UnloadSound(*sound);
  }
  sounds.clear();
}
