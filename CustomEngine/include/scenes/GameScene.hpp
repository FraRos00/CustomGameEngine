#pragma once
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "entities/Player.hpp"
#include "utils/Map.hpp"
#include "utils/Camera.hpp"
#include <raylib.h>

class GameScene : public Scene {
public:
  GameScene() : Scene("GameScene") {};

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;
  void HandleInputs() override {};
  
  ~GameScene() override = default;

private:
  EntityManager entityManager;
  Map map;
  GameCamera camera;
  Player *player = nullptr;
};
