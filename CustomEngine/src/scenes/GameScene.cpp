#include "scenes/GameScene.hpp"
#include "entities/Player.hpp"
#include "globals/config.hpp"
#include <raylib.h>

void GameScene::Init() {
  // inizializzare mappa
  map.Load("maps/map.json");
  //  inizializzare entity manager
  entityManager.AddEntity(std::make_unique<Player>(
      Vector2{config::SCREENWIDTH / 2.0f, config::SCREENHEIGHT / 2.0f},
      200.0f));

  //  inizializzare camera
  auto *player = entityManager.GetEntityOfType<Player>();
  if (player)
    this->player = player;
  else
    throw std::runtime_error("Player entity not found in GameScene Init");
  camera.SetTarget(player->GetPosition());
}

void GameScene::Update(float dt) {
  entityManager.UpdateAll(dt);
  camera.Update(player->GetPosition());
}

void GameScene::Draw() const {
  DrawFPS(10, 10);
  BeginMode2D(camera.GetCamera());
  map.Draw();
  entityManager.DrawAll();
  EndMode2D();
}
