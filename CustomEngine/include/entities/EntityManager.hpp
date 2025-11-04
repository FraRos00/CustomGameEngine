#pragma once
#include <memory>
#include <vector>
#include "entities/Entity.hpp"
#include "utils/Map.hpp"

class EntityManager {
public:
  void AddEntity(std::unique_ptr<Entity> entity);
  void UpdateAll(float dt);
  void DrawAll() const;
  void HandleMapCollisions(Map &map);
  void Clear();

  template <typename T> T *GetEntityOfType() {
    for (auto &entity : entities) {
      if (auto ptr = dynamic_cast<T *>(entity.get()))
        return ptr;
    }
    return nullptr;
  }

  template <typename T> std::vector<T *> GetEntitiesOfType() {
    std::vector<T *> result;
    for (auto &entity : entities) {
      if (auto ptr = dynamic_cast<T *>(entity.get()))
        result.push_back(ptr);
    }
    return result;
  }

private:
  std::vector<std::unique_ptr<Entity>> entities;
};
