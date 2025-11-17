#pragma once
#include "core/PhysicsManager.hpp"
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "entities/Player.hpp"
#include "ui/UiManager.hpp"
#include "utils/Camera.hpp"
#include "utils/Map.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <utility>

class GameScene : public Scene {
public:
  // forward serve a fare perfect forwarding ovvero trattare un rvalue e un
  // lvalue come tali e distinguerli quando vengono passati
  //  universal reference && rappresenta potenzialmente sia un rvalue sia un
  //  lvalue ed e' condizione necessaria per fare forwarding
  template <typename F>
  GameScene(F &&transition)
      : Scene("GameScene"), transition(std::forward<F>(transition)){};

  // GameScene()
  //: Scene("GameScene"){}

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;
  void LoadMap(std::string mapName);

  ~GameScene() override = default;

private:
  EntityManager entityManager;
  PhysicsManager physicsManager;
  UiManager uiManager;
  // TODO never delete currentMap in loadedMaps or currentMap will dangle
  // (use shared pointer?)
  Map *currentMap;
  std::unordered_map<std::string, std::unique_ptr<Map>> loadedMaps;
  GameCamera camera;
  Player *player = nullptr;
  std::function<void(std::function<void()>)> transition;
};
