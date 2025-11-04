#include <memory>
#include "scenes/PauseScene.hpp"



void PauseScene::Init() {
  InputManager &input = InputManager::GetInstance();
  
  pauseText = std::make_unique<Text>(
      "Game Paused", Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, global::fontSizes["h1"], RED);

  //input listeners
  
}
void PauseScene::Update(float dt) {
  // Logica di aggiornamento della scena di pausa (se necessario)
}
void PauseScene::Draw() const{
pauseText->Draw();
}