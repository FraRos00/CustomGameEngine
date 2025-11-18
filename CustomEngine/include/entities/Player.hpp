#pragma once

#include "Entity.hpp"
#include "animations/Animator.hpp"
#include "utils/InputSubscription.hpp"
#include <raylib.h>
#include <vector>

class Player : public Entity {
public:
  Player(Vector2 position, float velocity, bool isActive = true);

  // PUBLIC METHODS
  void Update(float dt) override;
  void Draw() const override;
  void OnCollision(Entity &other) override {};
  Rectangle GetHitboxRect() const override {
    float offsetX = hitbox.width / 2.0f;
    float offsetY = hitbox.height / 2.0f;
    return Rectangle{position.x - offsetX, position.y - offsetY, hitbox.width,
                     hitbox.height};
  }
  Rectangle GetNextHitboxRect() const override {
    float offsetX = hitbox.width / 2.0f;
    float offsetY = hitbox.height / 2.0f;
    return Rectangle{next.x - offsetX, next.y - offsetY, hitbox.width,
                     hitbox.height};
  }

  ~Player() = default;

private:
  void ChooseMoveAnimation(Vector2 dir);
  Vector2 dir = {0.0f, 0.0f};
  std::vector<InputSubscription> inputSubscriptions;
  Animator animator;
};
