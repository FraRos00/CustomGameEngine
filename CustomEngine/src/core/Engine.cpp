#include "core/Engine.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/PauseScene.hpp"
#include "globals/config.hpp"
#include "globals/globals.hpp"
#include <ctime>
#include <iostream>
#include <raylib.h>

void Engine::Init() {
  InitWindow(config::SCREENWIDTH, config::SCREENHEIGHT, "Custom Engine");
  SetTargetFPS(60);
  SetRandomSeed(time(nullptr));
  SetExitKey(KEY_NULL);
 
  InputManager &input = InputManager::GetInstance();

  // create game scenes
  auto *gameScene = new GameScene();
  auto *pauseScene = new PauseScene();

  gameScene->Init();
  pauseScene->Init();

  sceneManager.Register(gameScene);
  sceneManager.Register(pauseScene);
  
  // activate the game scene and push the input game context
  sceneManager.Push("GameScene");

  input.PushContext(InputContext::GameContext);

  //register inputs listeners
  inputSubscriptions.emplace_back(
    input.SubscribeListener(
      Action::ToggleDebugMode, InputEventType::Pressed,
       [](){global::DEBUG = !global::DEBUG;}
      )
  );

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
