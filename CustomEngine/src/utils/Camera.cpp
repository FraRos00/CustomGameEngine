#include "utils/Camera.hpp"
#include <raylib.h>
#include <raymath.h>


void GameCamera::Update(Vector2 target, float smoothness){
     camera.target = Vector2Lerp(camera.target, target, smoothness);

     float halfW = viewW * 0.5f;
     float halfH = viewH * 0.5f;

     // Clamp dei limiti
     if (camera.target.x < halfW)
     camera.target.x = halfW;
     if (camera.target.y < halfH)
     camera.target.y = halfH;
     if (camera.target.x > bgW - halfW)
     camera.target.x = bgW - halfW;
     if (camera.target.y > bgH - halfH)
     camera.target.y = bgH - halfH;

     // Se la mappa è più piccola della vista, centra la camera
     if (bgW < viewW)
     camera.target.x = bgW / 2;
     if (bgH < viewH)
     camera.target.y = bgH / 2;
}

void GameCamera::SetBounds(float backgroundWidth, float backgroundHeight){
  // --- Limiti della camera considerando lo zoom ---
  bgW = backgroundWidth;
  bgH = backgroundHeight;

  // Dimensione visibile in world space
  viewW = GetScreenWidth() / camera.zoom;
  viewH = GetScreenHeight() / camera.zoom;
}
