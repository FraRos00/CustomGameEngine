#include "animations/Animator.hpp"

void Animator::AddAnimation(const std::string &name,const Animation& animation){
    animations[name]=animation;
}

void Animator::Play(const std::string &name, bool forceRestart){
    auto it = animations.find(name);
    if(it==animations.end()) return;

    if(currentName == name && !forceRestart) return;
    currentName = name;
    currentAnimation = &it->second;
    currentAnimation->Reset();
    
}

void Animator::Update(float dt){
    if(currentAnimation)
        currentAnimation->Update(dt);
}

void Animator::Draw(Vector2 position, Color tint)const{
    if(currentAnimation)
        currentAnimation->Draw(position,tint);
}