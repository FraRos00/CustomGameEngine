#pragma once
#include "core/InputManager.hpp"
#include "core/ResourceManager.hpp"
#include "utils/InputSubscription.hpp"
#include "core/SceneManager.hpp"


class Engine {
  public:
    void Init();
    void Run();
    void Shutdown();

  private:
    SceneManager sceneManager;
    std::vector<InputSubscription> inputSubscriptions;


    bool isRunning = false;
};
