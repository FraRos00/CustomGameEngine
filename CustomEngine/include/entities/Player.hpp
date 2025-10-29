#pragma once

#include "Entity.hpp"
#include <raylib.h>

class Player : public Entity {
public:
  Player(Vector2 position, float velocity, bool isActive = true)
      : Entity(position, velocity, isActive) {
    hitbox = {position.x - 10.0f, position.y - 10.0f, 20.0f, 20.0f};
  };

  // PUBLIC METHODS
  void Update(float dt) override;
  void Draw() const override;
  void OnCollision(Entity &other) override {};

  Vector2 GetPosition() const { return position; }

  ~Player() = default;

private:
  Rectangle hitbox;
  Vector2 dir = {0.0f, 0.0f};
};
