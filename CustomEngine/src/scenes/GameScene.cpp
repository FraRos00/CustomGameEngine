#include <raylib.h>
#include "scenes/GameScene.hpp"
#include "entities/Player.hpp"
#include "globals/config.hpp"
#include "ui/elements/InventoryUi.hpp"
#include <iostream>


void GameScene::Init() {
  InputManager &input = InputManager::GetInstance();

  // inizializzare mappe in ordine inverso
  LoadMap("map");

  //  inizializzare player entity
  entityManager.AddEntity(std::make_unique<Player>(
      currentMap->ParseSpawnPoint(),
      200.0f));

  auto *player = entityManager.GetEntityOfType<Player>();
  if (player)
    this->player = player;
  else
    throw std::runtime_error("Player entity not found in GameScene Init");

  //  inizializzare camera
  camera.SetTarget(player->GetPosition());
  camera.SetBounds(currentMap->GetWidth(),currentMap->GetHeight());

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
  inputSubscriptions.emplace_back(
    input.SubscribeListener(
      Action::TestTransition, InputEventType::Pressed,
      transition
    )
  );

}

void GameScene::LoadMap(std::string mapName){
  auto it = loadedMaps.find(mapName);
  if(it!=loadedMaps.end()){
    currentMap = it->second.get();
    std::cout << "GameScene: switched to cached map " << mapName << "\n";
    return;
  }
  auto newMap = std::make_unique<Map>();
  std::string path = "maps/"+mapName+".json";

  if(!newMap->Load(path)) return;

  currentMap = newMap.get();
  loadedMaps[mapName] = std::move(newMap);

  std::cout << "GameScene: loaded and set map " << mapName << "\n";

}

void GameScene::Update(float dt) {
  entityManager.UpdateAll(dt);
  entityManager.HandleMapCollisions(*currentMap);
  camera.Update(player->GetPosition());
  uiManager.Update(dt);
}

void GameScene::Draw() const {
  
  BeginMode2D(camera.GetCamera());
  currentMap->Draw();
  entityManager.DrawAll();
  EndMode2D();

  uiManager.Draw();
}
