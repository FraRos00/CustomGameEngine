#pragma once
#include <unordered_map>
#include <string>
#include "animations/Animation.hpp"

class Animator{
    public:
    void AddAnimation(const std::string &name,const Animation& animation);
    void Play(const std::string &name, bool forceRestart=false);
    void Update(float dt);
    void Draw(Vector2 position, Color tint = WHITE)const;
    
    private:
    std::unordered_map<std::string, Animation>animations;    
    Animation* currentAnimation = nullptr;
    std::string currentName;
};