#include <raylib.h>
#include "scenes/GameScene.hpp"
#include "entities/Player.hpp"
#include "globals/config.hpp"
#include "ui/elements/InventoryUi.hpp"


void GameScene::Init() {
  InputManager &input = InputManager::GetInstance();

  // inizializzare mappa
  map.Load("maps/map.json");

  //  inizializzare player entity
  entityManager.AddEntity(std::make_unique<Player>(
      Vector2{config::SCREENWIDTH / 2.0f, config::SCREENHEIGHT / 2.0f},
      200.0f));

  auto *player = entityManager.GetEntityOfType<Player>();
  if (player)
    this->player = player;
  else
    throw std::runtime_error("Player entity not found in GameScene Init");

  //  inizializzare camera
  camera.SetTarget(player->GetPosition());

  // inizializzare ui elements
  InventoryUi* invPtr = uiManager.CreateElement<InventoryUi>();
  
  inputSubscriptions.emplace_back(
    input.SubscribeListener(
      Action::OpenInventory,InputEventType::Pressed,
      [invPtr, &input](){
        input.PushContext(InputContext::InventoryContext);
        invPtr->SetVisible(true);
      }
    )
  );

  // altri input
  

}

void GameScene::Update(float dt) {
  entityManager.UpdateAll(dt);
  entityManager.HandleMapCollisions(map);
  camera.Update(player->GetPosition());
  uiManager.Update(dt);
}

void GameScene::Draw() const {
  //DrawFPS(10, 10);
  
  BeginMode2D(camera.GetCamera());
  map.Draw();
  entityManager.DrawAll();
  EndMode2D();

  uiManager.Draw();
}
