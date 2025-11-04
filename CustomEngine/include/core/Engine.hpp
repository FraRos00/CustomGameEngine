#pragma once
#include "core/InputManager.hpp"
#include "core/ResourceManager.hpp"
#include "utils/InputSubscription.hpp"
#include "core/SceneManager.hpp"
#include "core/PhysicsManager.hpp"


class Engine {
  public:
    void Init();
    void Run();
    void Shutdown();

  private:
    SceneManager sceneManager;
    PhysicsManager physicsManager;
    std::vector<InputSubscription> inputSubscriptions;


    bool isRunning = false;
};
