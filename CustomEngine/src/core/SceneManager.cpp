#include "core/SceneManager.hpp"
#include <iostream>

void SceneManager::Register(Scene *scene) {
  if (!scene)
    return;
  std::string name = scene->GetName();
  scenes[name] = std::unique_ptr<Scene>(scene);
}

void SceneManager::Push(std::string name){
  auto it = scenes.find(name);
  if(it!=scenes.end()){
    sceneStack.push_back(it->second.get());
    std::cout << "SceneManager: pushed scene " << name << " onto the stack\n";
  }else{
    std::cout << "SceneManager: scene " << name << " not found\n";
  }
}

void SceneManager::Pop() {
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
  for(const auto& scene : sceneStack) {
    scene->Draw();
  }
}

std::string SceneManager::GetCurrentSceneName()const {
    if(!sceneStack.empty())
        return sceneStack.back()->GetName();
    return "";
}
