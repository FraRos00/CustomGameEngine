#include "entities/Player.hpp"
#include "core/InputManager.hpp"
#include <cmath>
#include <iostream>

Player::Player(Vector2 position, float velocity, bool isActive): Entity(position, velocity, isActive) {
    
  //Subscribe inputs
    InputManager &input = InputManager::GetInstance();

    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveUp, InputEventType::Held, [this](){dir.y-=1;})
    );
    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveDown, InputEventType::Held, [this](){dir.y+=1;})
    );
    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveRight, InputEventType::Held, [this](){dir.x+=1;})
    );
    inputSubscriptions.emplace_back( 
      input.SubscribeListener(Action::MoveLeft, InputEventType::Held, [this](){dir.x-=1;})
    );

    //Add Animations
    animator.AddAnimation("IdleFront",Animation("character/sSwordsman_lvl3_Idle_with_shadow.png",0,0,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleLeft",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,64,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleRight",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,128,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleBack",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,192,64,64,2,4,8.0f,true));
    
    animator.AddAnimation("RunFront",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,0,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunLeft",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,64,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunRight",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,128,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunBack",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,192,64,64,2,8,8.0f,true));

    animator.Play("IdleFront");
  }

void Player::Update(float dt) {

  if (dir.x != 0 || dir.y != 0) {
    float v_2 = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= v_2;
    dir.y /= v_2;

    position.x += dir.x * velocity * dt;
    position.y += dir.y * velocity * dt;
    
    if(dir.y==0 && dir.x<0) animator.Play("RunLeft");
    if(dir.y==0 && dir.x>0) animator.Play("RunRight");
    if(dir.y>0) animator.Play("RunFront");
    if(dir.y<0) animator.Play("RunBack");
  }else{
    animator.Play("IdleFront");
  }

  dir={0.0f, 0.0f};
  animator.Update(dt);

}

void Player::Draw() const { 
  animator.Draw(position);
 }
