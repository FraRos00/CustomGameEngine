#include "entities/Player.hpp"
#include "core/InputManager.hpp"
#include <cmath>

void Player::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.IsHeld(Action::MoveLeft)) {
    dir.x -= 1;
  }
  if (input.IsHeld(Action::MoveRight)) {
    dir.x += 1;
  }
  if (input.IsHeld(Action::MoveUp)) {
    dir.y -= 1;
  }
  if (input.IsHeld(Action::MoveDown)) {
    dir.y += 1;
  }
  if (dir.x != 0 || dir.y != 0) {
    float v_2 = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= v_2;
    dir.y /= v_2;

    position.x += dir.x * velocity * dt;
    position.y += dir.y * velocity * dt;
  }
  dir={0.0f, 0.0f};
}

void Player::Draw() const { DrawRectangleRec(Rectangle{position.x - 10.0f, position.y - 10.0f, 20.0f, 20.0f}, BLUE); }
