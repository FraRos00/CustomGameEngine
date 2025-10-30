#include "scenes/PauseScene.hpp"
#include "globals/globals.hpp"
#include <memory>

void PauseScene::Init() {
  pauseText = std::make_unique<Text>(
      "Game Paused", Vector2{400.0f, 300.0f}, global::fontSizes["h2"], RED);
}
void PauseScene::Update(float dt) {
  // Logica di aggiornamento della scena di pausa (se necessario)
}
void PauseScene::Draw() const{
pauseText->Draw();
}