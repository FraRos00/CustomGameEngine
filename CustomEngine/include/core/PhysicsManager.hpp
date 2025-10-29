#pragma once
#include "entities/Entity.hpp"
#include "utils/Map.hpp"

class PhysicsManager {
public:
  void ApplyPhysics(Entity &entity, float dt, Map &map);

private:
  float gravity;
};
