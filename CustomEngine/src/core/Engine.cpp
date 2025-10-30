#include "core/Engine.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/PauseScene.hpp"
#include "globals/config.hpp"
#include <ctime>
#include <iostream>
#include <raylib.h>

void Engine::Init() {
  InitWindow(config::SCREENWIDTH, config::SCREENHEIGHT, "Custom Engine");
  SetTargetFPS(60);
  SetRandomSeed(time(nullptr));
  SetExitKey(KEY_NULL);
 
  auto *gameScene = new GameScene();
  auto *pauseScene = new PauseScene();

  gameScene->Init();
  pauseScene->Init();

  sceneManager.Register(gameScene);
  sceneManager.Register(pauseScene);
  
  sceneManager.Push("GameScene");
}

void Engine::Run() {
  isRunning = true;
  float dt;
  while (isRunning && !WindowShouldClose()) {
    dt = GetFrameTime();

    if(inputManager.IsPressed(Action::Pause)) {
      if(sceneManager.GetCurrentSceneName() == "GameScene") {
        sceneManager.Push("PauseScene");
      } else {
        sceneManager.Pop();
      }
    }

    inputManager.Update();
    // update fisica
    sceneManager.Update(dt);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    sceneManager.Draw();
    EndDrawing();
  }

  Shutdown();
}

void Engine::Shutdown() {
  resourceManager.UnloadAll();
  CloseWindow();
}
