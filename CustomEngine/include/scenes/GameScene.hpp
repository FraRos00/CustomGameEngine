#pragma once
#include <raylib.h>
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "core/PhysicsManager.hpp"
#include "ui/UiManager.hpp"
#include "utils/Map.hpp"
#include "utils/Camera.hpp"
#include "entities/Player.hpp"


class GameScene : public Scene {
public:
  GameScene() : Scene("GameScene"){};

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;
  
  ~GameScene() override = default;

private:
  EntityManager entityManager;
  PhysicsManager physicsManager;
  UiManager uiManager;
  Map map;
  GameCamera camera;
  Player *player = nullptr;

};
