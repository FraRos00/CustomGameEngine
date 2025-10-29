#include "core/InputManager.hpp"
#include <raylib.h>

InputManager &InputManager::GetInstance() {
  static InputManager instance;
  return instance;
}

InputManager::InputManager() {
  bindings[Action::MoveLeft] = KEY_A;
  bindings[Action::MoveRight] = KEY_D;
  bindings[Action::MoveUp] = KEY_W;
  bindings[Action::MoveDown] = KEY_S;
  bindings[Action::Attack] = KEY_SPACE;
  bindings[Action::Pause] = KEY_ESCAPE;
}

void InputManager::Update() {
  for (auto &[action, key] : bindings) {
    InputState &state = states[action];
    state.isPressed = IsKeyPressed(key);
    state.isHeld = IsKeyDown(key);
    state.isReleased = IsKeyReleased(key);
  }
}

bool InputManager::IsPressed(Action action) const {
  auto it = states.find(action);
  return it != states.end() && it->second.isPressed;
}

bool InputManager::IsHeld(Action action) const {
  auto it = states.find(action);
  return it != states.end() && it->second.isHeld;
}

bool InputManager::IsReleased(Action action) const {
  auto it = states.find(action);
  return it != states.end() && it->second.isReleased;
}
