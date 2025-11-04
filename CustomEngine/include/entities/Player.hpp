#pragma once

#include <raylib.h>
#include <vector>
#include "Entity.hpp"
#include "utils/InputSubscription.hpp"
#include "animations/Animator.hpp"



class Player : public Entity {
public:
  Player(Vector2 position, float velocity, bool isActive = true);

  // PUBLIC METHODS
  void Update(float dt) override;
  void Draw() const override;
  void OnCollision(Entity &other) override {};

  ~Player() = default;

private:
  void ChooseMoveAnimation(Vector2 dir);
  Vector2 dir = {0.0f, 0.0f};
  std::vector<InputSubscription> inputSubscriptions;
  Animator animator;
  
};
