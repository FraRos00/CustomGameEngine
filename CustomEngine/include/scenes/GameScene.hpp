#pragma once
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "entities/Player.hpp"
#include "utils/Map.hpp"
#include <raylib.h>

class GameScene : public Scene {
public:
  GameScene() : Scene("GameScene") {};

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;
  void HandleInputs() override {};
  std::string GetName() const { return name; };

  ~GameScene() override = default;

private:
  EntityManager entityManager;
  Map map;
  Camera2D camera;

  Player *player = nullptr;
};
