#include "entities/Player.hpp"
#include "core/InputManager.hpp"
#include "globals/globals.hpp"
#include <iostream>

Player::Player(Vector2 position, float velocity, bool isActive): Entity(position, velocity, isActive){
    
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
    animator.AddAnimation("IdleFront",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,0,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleLeft",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,64,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleRight",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,128,64,64,2,12,8.0f,true));
    animator.AddAnimation("IdleBack",Animation("character/Swordsman_lvl3_Idle_with_shadow.png",0,192,64,64,2,4,2.0f,true));
    
    animator.AddAnimation("RunFront",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,0,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunLeft",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,64,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunRight",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,128,64,64,2,8,8.0f,true));
    animator.AddAnimation("RunBack",Animation("character/Swordsman_lvl3_Run_with_shadow.png",0,192,64,64,2,8,8.0f,true));

    animator.Play("IdleFront");

    //hitbox TO FIX, devo scalarla
    hitbox.width = 64.0f/2;
    hitbox.height = 64.0f/2;
  }

void Player::Update(float dt) {

  if (dir.x != 0 || dir.y != 0)
    next = Move(position,dir,dt);

  ChooseMoveAnimation(dir);
  dir={0.0f, 0.0f};
  animator.Update(dt);

}



void Player::Draw() const { 
  animator.Draw(position);

  if(global::DEBUG){
  float offsetX = hitbox.width/2.0f;
  float offsetY = hitbox.height/2.0f;
  DrawRectangleLines(
    position.x-offsetX, position.y-offsetY,
    hitbox.width,hitbox.height,
    RED);
  }
 }


void Player::ChooseMoveAnimation(Vector2 dir){
  if (dir.x != 0 || dir.y != 0) {
    //chose running animation
    if(dir.y==0){
      if(dir.x<0) animator.Play("RunLeft");
      else animator.Play("RunRight");
    }else{
      if(dir.y>0) animator.Play("RunFront");
      else animator.Play("RunBack");
    }

  }else{
    std::string currentAnimation = animator.GetCurrentAnimation();
    if(currentAnimation!="IdleFront" && 
      currentAnimation!="IdleBack" &&
      currentAnimation!="IdleRight" &&
      currentAnimation!="IdleLeft"){
        if(currentAnimation == "RunLeft")
          animator.Play("IdleLeft");
        else if(currentAnimation == "RunRight")
          animator.Play("IdleRight");
        else if(currentAnimation == "RunBack")
          animator.Play("IdleBack");
        else
          animator.Play("IdleFront");
      }
  }
}