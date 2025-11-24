#include "core/ShaderManager.hpp"
#include <iostream>
#include <memory>
#include <raylib.h>

ShaderManager &ShaderManager::GetInstance() {
  static ShaderManager instance;
  return instance;
}

void ShaderManager::Load(const std::string &name, const std::string &vspath,
                         const std::string &fspath) {
  auto it = shaders.find(name);
  if (it != shaders.end()) {
    return;
  }

  auto shader = std::make_unique<Shader>();
  *shader = LoadShader(vspath.c_str(), fspath.c_str());
  if (shader->locs != nullptr) {
    shaders[name] = std::move(shader);
    std::cout << "[DEBUG!!] Shader loaded successfully" << std::endl;
  } else {
    UnloadShader(*shader);
  }
}

Shader *ShaderManager::GetShader(const std::string &name) {
  auto it = shaders.find(name);
  if (it != shaders.end()) {
    std::cout << "[DEBUG!!!] VALID SHADER PTR RETURN!!!!!!!" << std::endl;
    return it->second.get();
  }

  std::cout << "[DEBUG!!!] NULL PTR RETURN!!!!!!!" << std::endl;
  return nullptr;
}

int ShaderManager::GetLocation(const std::string &name,
                               const std::string &uniform) {
  auto it = shaders.find(name);
  if (it == shaders.end())
    return -1;

  return GetShaderLocation(*it->second, uniform.c_str());
}

void ShaderManager::Set(const std::string &name, const std::string &uniform,
                        const void *value, int type) {

  auto it = shaders.find(name);
  if (it == shaders.end())
    return;
  int loc = GetLocation(name, uniform);
  if (loc < 0)
    return;
  SetShaderValue(*it->second, loc, value, type);
}

void ShaderManager::UnloadAll() {
  for (auto &[_, shader] : shaders) {
    if (shader)
      UnloadShader(*shader);
  }
  shaders.clear();
}
