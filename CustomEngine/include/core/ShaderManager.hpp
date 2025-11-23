#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>

class ShaderManager {
public:
  static ShaderManager &GetInstance();
  void Load(const std::string &name, const std::string &vspath,
            const std::string &fspath);

  void Unload(const std::string &name);

  Shader *GetShader(const std::string &name);

  int GetLocation(const std::string &name, const std::string &uniform);

  void Set(const std::string &shaderName, const std::string &uniform,
           const void *value, int type);

  void UnloadAll();

private:
  ShaderManager() = default;
  ~ShaderManager() { UnloadAll(); }
  ShaderManager(const ShaderManager &) = delete;
  ShaderManager &operator=(const ShaderManager &) = delete;

  std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
  // std::unordered_map<std::string, int> locations;
};
