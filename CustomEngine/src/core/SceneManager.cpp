#include "core/SceneManager.hpp"
#include <iostream>

void SceneManager::Push(Scene *scene) {
  if (!scene)
    return;
  std::string name = scene->GetName();
  scenes[name] = std::unique_ptr<Scene>(scene);
}

void SceneManager::Pop() {
  if (!currentScene)
    return;
  std::string name = currentScene->GetName();
  scenes.erase(name);
  currentScene = nullptr;
}

void SceneManager::Switch(std::string name) {
  auto it = scenes.find(name);
  if (it != scenes.end()) {
    currentScene = it->second.get();
    std::cout << "SceneManager: switched to scene '" << name << "'.\n";
  } else
    std::cout << "SceneManager: scene '" << name << "' not found.\n";
}

void SceneManager::Update(float dt) {
  if (currentScene)
    currentScene->Update(dt);
}

void SceneManager::Draw() const {
  if (currentScene)
    currentScene->Draw();
}
