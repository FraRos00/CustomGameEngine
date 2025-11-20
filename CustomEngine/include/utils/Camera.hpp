#pragma once
#include "globals/config.hpp"
#include <raylib.h>

class GameCamera {
public:
  GameCamera(Vector2 target = {GetScreenWidth() / 2.0f,
                               GetScreenHeight() / 2.0f},
             float zoom = 1.0f,
             Vector2 offset = {config::SCREENWIDTH / 2.0f,
                               config::SCREENHEIGHT / 2.0f},
             float rotation = 0.0f)
      : camera{target, offset, rotation, zoom} {};
  void SetTarget(Vector2 target) { camera.target = target; };
  void SetBounds(float backgroundWidth, float backgroundHeight);
  void Update(Vector2 target, float smoothness = 0.1f);
  Camera2D GetCamera() const { return camera; };

private:
  Camera2D camera;

  // --- Limiti della camera considerando lo zoom ---
  float bgW;
  float bgH;

  // Dimensione visibile in world space
  float viewW;
  float viewH;
};
