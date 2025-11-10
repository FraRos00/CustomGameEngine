#pragma once
#include <string>
#include "core/InputManager.hpp"
#include "globals/globals.hpp"
#include "utils/InputSubscription.hpp"


class Scene {
public:
  Scene(std::string name) : name(std::move(name)) {}
  virtual ~Scene() = default;

  virtual void Init() = 0;
  virtual void Update(float dt) = 0;
  virtual void Draw() const = 0;

  virtual void Reset(){}

  std::string GetName() const { return name; }

protected:
  std::string name;
  std::vector<InputSubscription> inputSubscriptions;

};
