#include "scenes/GameScene.hpp"
#include "entities/Player.hpp"
#include "ui/elements/InventoryUi.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <raylib.h>

void GameScene::Init() {
  InputManager &input = InputManager::GetInstance();

  SwitchToMap("map");
  // LoadNeighbourMaps();
  ParseLoadedMaps();
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

void GameScene::SwitchToMap(std::string mapName) {

  LoadMap(mapName);
  currentMap = loadedMaps.Get(mapName);

  std::cout << "GameScene: switched to map " << mapName << "\n";
}

void GameScene::LoadMap(std::string mapName) {
  auto it = loadedMaps.Get(mapName);
  if (it != nullptr)
    return;

  auto newMap = std::make_unique<Map>();
  std::string path = "maps/" + mapName + ".json";

  if (!newMap->LoadMapTexture(path))
    return;

  loadedMaps.Put(mapName, std::move(newMap),
                 currentMap ? currentMap->GetMapName() : "");
  std::cout << "GameScene: loaded map " << mapName << "\n";
}

void GameScene::TransitionToMap(std::string newMapName,
                                std::string currentMapName) {

  auto beforeTask = [this, newMapName]() { SwitchToMap(newMapName); };

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

void GameScene::LoadNeighbourMaps() {

  auto neighbourMaps = currentMap->GetAllTeleportZones();
  for (const auto &mapName : neighbourMaps) {
    LoadMap(mapName);
  }
}

void GameScene::ParseLoadedMaps() {
  auto maps = loadedMaps.GetAll();
  for (const auto map : maps) {
    map->ParseMapData();
  }
}

void GameScene::Update(float dt) {
  entityManager.UpdateAll(dt);
  entityManager.HandleMapCollisions(*currentMap);

  std::string teleportMapName =
      currentMap->CheckTeleport(player->GetHitboxRect());

  if (!teleportMapName.empty()) {
    // TODO: che succede se il player si teletrasporta di nuovo prima che
    // mapsReady sia true?
    TransitionToMap(teleportMapName, currentMap->GetMapName());
    madeTransition = true;
  } else {
    camera.Update(player->GetPosition());
    uiManager.Update(dt);

    if (madeTransition) {
      // TransitionToMap non fa fermare l'esecuzione... l'update finisce anche
      // mentre transitionscene è attiva prima di mettersi in pausa
      madeTransition = false;
      mapsReady = false;
      LoadNeighbourMaps();
      parseFuture =
          std::async(std::launch::async, [this]() { ParseLoadedMaps(); });
    }
  }

  if (!mapsReady && parseFuture.valid()) {
    auto status = parseFuture.wait_for(std::chrono::milliseconds(0));

    if (status == std::future_status::ready) {
      parseFuture.get();
      mapsReady = true;
    }
  }
}

void GameScene::Draw() const {
  BeginMode2D(camera.GetCamera());
  currentMap->Draw();
  entityManager.DrawAll();
  EndMode2D();

  uiManager.Draw();
}
