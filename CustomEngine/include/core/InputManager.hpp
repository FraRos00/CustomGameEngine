#pragma once

#include <raylib.h>
#include <unordered_map>
enum class Action {
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  Jump,
  Attack,
  Pause
};

struct InputState {
  bool isPressed = false;
  bool isHeld = false;
  bool isReleased = false;
};

class InputManager {

public:
  static InputManager &GetInstance();
  void Update();

  bool IsPressed(Action action) const;
  bool IsHeld(Action action) const;
  bool IsReleased(Action action) const;

  void BindKey(Action action, KeyboardKey key);

private:
  // Costruttore privato → impedisce la creazione diretta
  InputManager();
  // Impedisce copia o assegnazione
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;

  std::unordered_map<Action, KeyboardKey> bindings;
  std::unordered_map<Action, InputState> states;
};
