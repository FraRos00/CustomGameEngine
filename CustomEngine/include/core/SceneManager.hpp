#pragma once

#include "core/Scene.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class SceneManager {

public:
  void Push(Scene *scene);
  void Pop();
  void Switch(std::string name);
  void Update(float dt);
  void Draw() const;

private:
  std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
  Scene *currentScene = nullptr;
};
