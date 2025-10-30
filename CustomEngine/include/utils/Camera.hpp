#pragma once
#include <raylib.h>

class Camera{
    public:
    Camera(Vector2 target,float zoom = 2.0f ,Vector2 offset = {config::SCREENWIDTH / 2.0f, config::SCREENHEIGHT / 2.0f}, float rotation = 0.0f): camera {target, offset, rotation, zoom} {} ;
    void Update(Vector2 target);
    Camera2D GetCamera() const { return camera; };
    
    private:
    Camera2D camera;
}