#pragma once
#include "core/InputManager.hpp"
#include "core/PhysicsManager.hpp"
#include "core/ResourceManager.hpp"
#include "core/SceneManager.hpp"

class Engine {
public:
  void Init();
  void Run();
  void Shutdown();

private:
  SceneManager sceneManager;
  PhysicsManager physicsManager;
  InputManager &inputManager = InputManager::GetInstance();
  ResourceManager &resourceManager = ResourceManager::GetInstance();

  bool isRunning = false;
};
