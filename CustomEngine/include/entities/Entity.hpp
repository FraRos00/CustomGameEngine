#pragma once
#include <cmath>
#include <raylib.h>

struct Hitbox {
  float width;
  float height;
};

class Entity {
public:
  Entity(Vector2 position, float velocity, bool isActive = true)
      : position(position), next(position), velocity(velocity),
        isActive(isActive) {}

  Entity(Entity &&other) noexcept
      : position(other.position), velocity(other.velocity),
        isActive(other.isActive) {}

  virtual void Update(float dt) = 0;
  virtual void Draw() const = 0;
  virtual void OnCollision(Entity &other) = 0;

  Vector2 GetPosition() const { return position; }
  Vector2 GetNextPosition() const { return next; }
  void SetPosition(Vector2 position) { this->position = position; }
  void SetNextPosition(Vector2 next) { this->next = next; }
  Hitbox GetHitbox() const { return hitbox; }

  virtual ~Entity() = default;

protected:
  Vector2 Move(Vector2 position, Vector2 dir, float dt) {
    float v_2 = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= v_2;
    dir.y /= v_2;

    position.x += dir.x * velocity * dt;
    position.y += dir.y * velocity * dt;

    return position;
  }

  Vector2 position;
  Vector2 next = {0.0f, 0.0f};

  float velocity;
  Hitbox hitbox;

  bool isActive;
};
