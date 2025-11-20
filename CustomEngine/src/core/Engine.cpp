#include "core/Engine.hpp"
#include "globals/config.hpp"
#include "globals/globals.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/PauseScene.hpp"
#include "scenes/TransitionScene.hpp"
#include <ctime>
#include <iostream>
#include <raylib.h>

void Engine::Init() {
  // fix scaling problems on wayland
  InitWindow(config::SCREENWIDTH/2, config::SCREENHEIGHT/2, "Custom Engine");
  SetTargetFPS(60);
  SetRandomSeed(time(nullptr));
  SetExitKey(KEY_Q);

  InputManager &input = InputManager::GetInstance();

  // create game scenes
  auto *gameScene =
      new GameScene([&input, this](std::function<void()> beforeTask,
                                   std::function<void()> asyncTask,
                                   std::function<void()> afterTask) {
        auto *transitionScene = new TransitionScene(
            [&input, this]() {
              input.PopContext();
              this->sceneManager.Pop();
              this->sceneManager.Unregister("TransitionScene");
            },
            beforeTask, asyncTask, afterTask);

        input.PushContext(InputContext::TransitionContext);
        this->sceneManager.Register(transitionScene);
        this->sceneManager.Push("TransitionScene");
      });

  auto *pauseScene = new PauseScene();

  sceneManager.Register(gameScene);
  sceneManager.Register(pauseScene);

  // activate the game scene and push the input game context
  sceneManager.Push("GameScene");
  input.PushContext(InputContext::GameContext);

  // register inputs listeners
  inputSubscriptions.emplace_back(
      input.SubscribeListener(Action::ToggleDebugMode, InputEventType::Pressed,
                              []() { global::DEBUG = !global::DEBUG; }));
}

void Engine::Run() {
  InputManager &inputManager = InputManager::GetInstance();
  isRunning = true;
  float dt;
  while (isRunning && !WindowShouldClose()) {
    dt = GetFrameTime();

    inputManager.Update();
    // update fisica
    sceneManager.Update(dt);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    sceneManager.Draw();
    DrawFPS(10, 10);
    EndDrawing();
  }

  Shutdown();
}

void Engine::Shutdown() {
  ResourceManager::GetInstance().UnloadAll();
  CloseWindow();
}
