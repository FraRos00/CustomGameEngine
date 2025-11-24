#pragma once
#include <raylib.h>
#include <string>

class Animation {
public:
  Animation() = default;
  Animation(std::string ssPath, int startX, int startY, int frameWidth,
            int frameHeight, float scale, int frameCount,
            float frameSpeed = 12.0f, bool loop = true);

  Animation(const Animation &other);
  Animation &operator=(const Animation &other);

  Animation(Animation &&other) noexcept;
  Animation &operator=(Animation &&other) noexcept;

  void Update(float dt);
  void Draw(Vector2 position, Color tint = WHITE) const;
  void Reset();
  bool IsFinished() const { return !loop && currentFrame >= frameCount; }

  ~Animation();

private:
  std::string ssPath = "";
  Texture2D *spritesheet = nullptr;
  Shader *shader;
  int frameCount = 0;
  int currentFrame = 0;
  float frameSpeed = 12.0f; // we want to animate at 12FPS
  float timer = 0.0f;
  int frameWidth = 0;
  int frameHeight = 0;
  float scale = 0.0f;
  int startX = 0;
  int startY = 0;
  bool loop = true;
};
