#pragma once
#include <raylib.h>
#include "core/Scene.hpp"
#include "entities/EntityManager.hpp"
#include "entities/Player.hpp"
#include "utils/Map.hpp"
#include "utils/Camera.hpp"
#include "ui/UiManager.hpp"


class GameScene : public Scene {
public:
  GameScene() : Scene("GameScene"){};

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;
  
  ~GameScene() override = default;

private:
  EntityManager entityManager;
  UiManager uiManager;
  Map map;
  GameCamera camera;
  Player *player = nullptr;

};
