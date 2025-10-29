#pragma once
#include <raylib.h>

class Entity {
public:
  Entity(Vector2 position, float velocity, bool isActive = true)
      : position(position), velocity(velocity), isActive(isActive) {}

  Entity(Entity &&other) noexcept
      : position(other.position), velocity(other.velocity),
        isActive(other.isActive) {}

  virtual void Update(float dt) = 0;
  virtual void Draw() const = 0;
  virtual void OnCollision(Entity &other) = 0;

  virtual ~Entity() = default;

protected:
  Vector2 position;
  float velocity;
  Texture2D texture;
  Rectangle boundingBox;
  bool isActive;
};
