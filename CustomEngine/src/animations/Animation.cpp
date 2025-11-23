#include "animations/Animation.hpp"
#include "core/ResourceManager.hpp"
#include "core/ShaderManager.hpp"
#include <raylib.h>

Animation::Animation(std::string ssPath, int startX, int startY, int frameWidth,
                     int frameHeight, float scale, int frameCount,
                     float frameSpeed, bool loop)
    : ssPath(ssPath), frameCount(frameCount), frameSpeed(frameSpeed),
      frameWidth(frameWidth), frameHeight(frameHeight), scale(scale),
      startX(startX), startY(startY), loop(loop) {
  ResourceManager &rm = ResourceManager::GetInstance();
  rm.LoadTextureFromPath(ssPath);
  spritesheet = rm.GetTexture(ssPath);
  shader = ShaderManager::GetInstance().GetShader("red");
}

Animation::Animation(const Animation &other)
    : ssPath(other.ssPath), frameCount(other.frameCount),
      currentFrame(other.currentFrame), frameSpeed(other.frameSpeed),
      timer(other.timer), frameWidth(other.frameWidth),
      frameHeight(other.frameHeight), scale(other.scale), startX(other.startX),
      startY(other.startY), loop(other.loop) {

  if (!ssPath.empty()) {
    ResourceManager &rm = ResourceManager::GetInstance();
    rm.LoadTextureFromPath(ssPath); // aumenta refcount
    spritesheet = rm.GetTexture(ssPath);
  }
}

Animation &Animation::operator=(const Animation &other) {

  if (this != &other) {
    // se avevo gia una texture caricata prima di copiare la rilascio
    if (!ssPath.empty())
      ResourceManager::GetInstance().UnloadTextureFromPath(ssPath);

    // Copia dei dati
    ssPath = other.ssPath;
    startX = other.startX;
    startY = other.startY;
    frameWidth = other.frameWidth;
    frameHeight = other.frameHeight;
    scale = other.scale;
    frameCount = other.frameCount;
    frameSpeed = other.frameSpeed;
    loop = other.loop;
    currentFrame = other.currentFrame;
    timer = other.timer;

    if (!ssPath.empty()) {
      ResourceManager &rm = ResourceManager::GetInstance();
      rm.LoadTextureFromPath(ssPath);
      spritesheet = rm.GetTexture(ssPath);
    } else {
      spritesheet = nullptr;
    }
  }
  return *this;
}

Animation::Animation(Animation &&other) noexcept
    : ssPath(std::move(other.ssPath)), spritesheet(other.spritesheet),
      frameCount(other.frameCount), currentFrame(other.currentFrame),
      frameSpeed(other.frameSpeed), timer(other.timer),
      frameWidth(other.frameWidth), frameHeight(other.frameHeight),
      scale(other.scale), startX(other.startX), startY(other.startY),
      loop(other.loop) {

  other.spritesheet = nullptr;
  other.ssPath.clear();
}

Animation &Animation::operator=(Animation &&other) noexcept {
  if (this == &other)
    return *this;

  if (!ssPath.empty())
    ResourceManager::GetInstance().UnloadTextureFromPath(ssPath);

  ssPath = std::move(other.ssPath);
  spritesheet = other.spritesheet;
  frameCount = other.frameCount;
  currentFrame = other.currentFrame;
  frameSpeed = other.frameSpeed;
  timer = other.timer;
  frameWidth = other.frameWidth;
  frameHeight = other.frameHeight;
  scale = other.scale;
  startX = other.startX;
  startY = other.startY;
  loop = other.loop;

  other.spritesheet = nullptr;
  other.ssPath.clear();

  return *this;
}

Animation::~Animation() {
  ResourceManager::GetInstance().UnloadTextureFromPath(ssPath);
}

void Animation::Update(float dt) {
  timer += dt;
  if (timer >= 1.0f / frameSpeed) {
    timer = 0.0f;
    currentFrame = loop ? (currentFrame + 1) % frameCount : currentFrame + 1;
  }
}

void Animation::Draw(Vector2 position, Color tint) const {
  Rectangle dst{position.x, position.y, frameWidth * scale,
                frameHeight * scale};
  if (spritesheet) {
    int frameX = startX + currentFrame * frameWidth;
    Rectangle src{(float)frameX, (float)startY, (float)frameWidth,
                  (float)frameHeight};
    BeginShaderMode(*shader);
    DrawTexturePro(*spritesheet, src, dst,
                   {frameWidth * scale / 2, frameHeight * scale / 2}, 0.0f,
                   tint);
    EndShaderMode();
  } else {
    DrawRectangleRec(dst, RED);
  }
}

void Animation::Reset() {
  currentFrame = 0;
  timer = 0.0f;
}
