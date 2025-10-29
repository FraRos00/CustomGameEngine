#pragma once
#include "core/InputManager.hpp"
#include <string>

class Scene {
public:
  Scene(std::string name) : name(std::move(name)) {}
  virtual ~Scene() = default;

  virtual void Init() = 0;
  virtual void Update(float dt) = 0;
  virtual void Draw() const = 0;

  virtual void HandleInputs() = 0;

  std::string GetName() const { return name; }

protected:
  std::string name;
};
