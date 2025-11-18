#include "scenes/GameScene.hpp"
#include "entities/Player.hpp"
#include "globals/config.hpp"
#include "ui/elements/InventoryUi.hpp"
#include <iostream>
#include <raylib.h>

void GameScene::Init() {
  InputManager &input = InputManager::GetInstance();

  // inizializzare mappe in ordine inverso
  LoadMap("map");
  currentMap->ParseMapData();

  //  inizializzare player entity
  entityManager.AddEntity(
      std::make_unique<Player>(currentMap->GetSpawnPoint(), 200.0f));

  auto *player = entityManager.GetEntityOfType<Player>();
  if (player)
    this->player = player;
  else
    throw std::runtime_error("Player entity not found in GameScene Init");

  //  inizializzare camera
  camera.SetTarget(player->GetPosition());
  camera.SetBounds(currentMap->GetWidth(), currentMap->GetHeight());

  // inizializzare ui elements
  InventoryUi *invPtr = uiManager.CreateElement<InventoryUi>();

  inputSubscriptions.emplace_back(input.SubscribeListener(
      Action::OpenInventory, InputEventType::Pressed, [invPtr, &input]() {
        input.PushContext(InputContext::InventoryContext);
        invPtr->SetVisible(true);
      }));

  // altri input
  inputSubscriptions.emplace_back(input.SubscribeListener(
      Action::TestTransition, InputEventType::Pressed,
      [this]() { transition([]() {}, []() {}, []() {}); }));
}

void GameScene::LoadMap(std::string mapName) {
  // TODO implement a proper cache eviction policy and a cache mechanism
  // that makes sense
  auto it = loadedMaps.find(mapName);
  if (it != loadedMaps.end()) {
    currentMap = it->second.get();
    std::cout << "GameScene: switched to cached map " << mapName << "\n";
    return;
  }
  auto newMap = std::make_unique<Map>();
  std::string path = "maps/" + mapName + ".json";

  if (!newMap->LoadMapTexture(path))
    return;

  currentMap = newMap.get();
  loadedMaps[mapName] = std::move(newMap);

  std::cout << "GameScene: loaded and set map " << mapName << "\n";
}

void GameScene::SwitchToMap(std::string mapName, std::string currentMapName) {

  auto beforeTask = [this, mapName]() { LoadMap(mapName); };

  auto asyncTask = [this]() { currentMap->ParseMapData(); };

  auto afterTask = [this, currentMapName]() {
    Vector2 playerSpawnPoint = currentMap->GetTeleportZoneRect(currentMapName);
    player->SetPosition(playerSpawnPoint);
    player->SetNextPosition(player->GetPosition());

    camera.SetTarget(player->GetPosition());
    camera.SetBounds(currentMap->GetWidth(), currentMap->GetHeight());
    camera.Update(player->GetPosition());
  };
  std::cout << "Starting transition...\n";
  transition(beforeTask, asyncTask, afterTask);
}

void GameScene::Update(float dt) {
  entityManager.UpdateAll(dt);
  entityManager.HandleMapCollisions(*currentMap);

  std::string teleportMapName =
      currentMap->CheckTeleport(player->GetHitboxRect());

  if (!teleportMapName.empty()) {
    SwitchToMap(teleportMapName, currentMap->GetMapName());
  } else {
    camera.Update(player->GetPosition());
    uiManager.Update(dt);
  }
}

void GameScene::Draw() const {
  BeginMode2D(camera.GetCamera());
  currentMap->Draw();
  entityManager.DrawAll();
  EndMode2D();

  uiManager.Draw();
}
