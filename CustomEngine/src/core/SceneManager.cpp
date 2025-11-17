#include "core/SceneManager.hpp"
#include <iostream>

SceneManager::SceneManager() {
  InputManager &input = InputManager::GetInstance();

  inputSubscriptions.emplace_back(input.SubscribeListener(
      Action::Pause, InputEventType::Pressed, [&input, this]() {
        input.PushContext(InputContext::PauseContext);
        this->Push("PauseScene");
      }));

  inputSubscriptions.emplace_back(input.SubscribeListener(
      Action::UnPause, InputEventType::Pressed, [&input, this]() {
        input.PopContext();
        this->Pop();
      }));
}

void SceneManager::Register(Scene *scene) {
  if (!scene)
    return;
  std::string name = scene->GetName();
  scenes[name] = std::unique_ptr<Scene>(scene);
}

void SceneManager::Unregister(const std::string &name) { scenes.erase(name); }

void SceneManager::Push(std::string name) {
  auto it = scenes.find(name);
  if (it != scenes.end()) {
    it->second->Init();
    sceneStack.push_back(it->second.get());
    std::cout << "SceneManager: pushed scene " << name << " onto the stack\n";
  } else {
    std::cout << "SceneManager: scene " << name << " not found\n";
  }
}

void SceneManager::Pop() {
  std::cout << "SceneManager: popped a scene from the stack\n";
  if (sceneStack.empty())
    return;
  sceneStack.pop_back();
}

void SceneManager::Switch(std::string name) {
  sceneStack.clear();
  Push(name);
}

void SceneManager::Update(float dt) {
  if (!sceneStack.empty())
    sceneStack.back()->Update(dt);
}

void SceneManager::Draw() const {
  for (const auto &scene : sceneStack) {
    scene->Draw();
  }
}

std::string SceneManager::GetCurrentSceneName() const {
  if (!sceneStack.empty())
    return sceneStack.back()->GetName();
  return "";
}
