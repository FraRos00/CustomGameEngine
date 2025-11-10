#pragma once
#include <raylib.h>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "core/PhysicsManager.hpp"
#include "ui/UiManager.hpp"
#include "utils/Map.hpp"
#include "utils/Camera.hpp"
#include "entities/Player.hpp"


class GameScene : public Scene {
public:
  //forward serve a fare perfect forwarding ovvero trattare un rvalue e un lvalue come tali e distinguerli quando vengono passati
  // universal reference && rappresenta potenzialmente sia un rvalue sia un lvalue ed e' condizione necessaria per fare forwarding
  template<typename F>
  GameScene(F&& transition) 
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
  Map *currentMap;
  std::unordered_map<std::string, std::unique_ptr<Map>> loadedMaps;
  GameCamera camera;
  Player *player = nullptr;
  std::function<void()> transition;
};
