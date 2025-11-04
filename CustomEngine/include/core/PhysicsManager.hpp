#pragma once
#include "entities/EntityManager.hpp"
#include "utils/Map.hpp"

class PhysicsManager {
public:
  void CheckCollisions(EntityManager &entity, Map &map);

private:
  float gravity;
};
