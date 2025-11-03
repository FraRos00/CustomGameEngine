#include "utils/Camera.hpp"
#include <raymath.h>


void GameCamera::Update(Vector2 target){
     camera.target = Vector2Lerp(camera.target, target, 0.1f);
}