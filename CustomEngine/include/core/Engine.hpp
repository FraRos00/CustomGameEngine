#pragma once
#include "utils/InputSubscription.hpp"
#include "core/SceneManager.hpp"


class Engine {
  public:
    void Init(float scale);
    void Run();
    void Shutdown();

  private:
    SceneManager sceneManager;
    std::vector<InputSubscription> inputSubscriptions;


    bool isRunning = false;
};
