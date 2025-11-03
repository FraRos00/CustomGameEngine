#pragma once
#include <raylib.h>
#include "globals/config.hpp"

class GameCamera{
    public:
    GameCamera(Vector2 target={config::SCREENWIDTH / 2.0f, config::SCREENHEIGHT / 2.0f},float zoom = 2.0f ,Vector2 offset = {config::SCREENWIDTH / 2.0f, config::SCREENHEIGHT / 2.0f}, float rotation = 0.0f): camera {target, offset, rotation, zoom} {} ;
    void SetTarget(Vector2 target){ camera.target = target; };
    void Update(Vector2 target);
    Camera2D GetCamera() const { return camera; };
    
    private:
    Camera2D camera;
};