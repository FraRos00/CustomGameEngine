#pragma once

#include "core/Scene.hpp"
#include "utils/InputSubscription.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class SceneManager {

public:
  SceneManager();
  void Register(Scene *scene);
  void Unregister(const std::string &name);
  void Push(std::string name);
  void Pop();
  void Switch(std::string name);
  void Update(float dt);
  void Draw() const;
  std::string GetCurrentSceneName() const;

private:
  std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
  std::vector<Scene *> sceneStack;
  std::vector<InputSubscription> inputSubscriptions;
};
