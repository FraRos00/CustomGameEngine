#include "entities/Player.hpp"
#include "core/InputManager.hpp"
#include <cmath>
#include <iostream>

Player::Player(Vector2 position, float velocity, bool isActive): Entity(position, velocity, isActive) {
    hitbox = {position.x - 10.0f, position.y - 10.0f, 20.0f, 20.0f};
    InputManager &input = InputManager::GetInstance();

  
    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveRight, InputEventType::Held, [this](){dir.x+=1;})
    );

    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveUp, InputEventType::Held, [this](){dir.y-=1;})
    );
    
    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveDown, InputEventType::Held, [this](){dir.y+=1;})
    );
      inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveLeft, InputEventType::Held, [this](){dir.x-=1;})
    );


  }

void Player::Update(float dt) {

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
