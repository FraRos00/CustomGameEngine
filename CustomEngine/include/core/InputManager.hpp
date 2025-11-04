#pragma once
#include <raylib.h>
#include <unordered_map>
#include <functional>

enum class Action { 
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  Jump,
  Attack,
  Pause,
  UnPause,
  OpenInventory,
  CloseInventory,
  InventoryUp,
  InventoryDown,
  InventoryLeft,
  InventoryRight
};

enum class InputContext{
  GameContext,
  InventoryContext,
  PauseContext
};

enum class InputEventType {
  Pressed,
  Held,
  Released
};

struct InputState {
  bool isPressed = false;
  bool isHeld = false;
  bool isReleased = false;
};

struct ListenerCallback{
  int listenerId;
  std::function<void()> callback;
};

class InputManager {

public:
  static InputManager &GetInstance();

  void SwitchContext(InputContext inputContext);
  void PushContext(InputContext inputContext);
  void PopContext();

  int SubscribeListener(Action action, InputEventType eventType, std::function<void()> callback);
  void UnsubscribeListener(int id);
  void Update();

  //void BindKey(InputContext inputContext,Action action, KeyboardKey key);


private:
  InputManager();
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;
  void Dispatch(Action action, InputEventType type);

  std::unordered_map<
    InputContext,
    std::unordered_map<Action, KeyboardKey>
  > bindings;

  std::unordered_map<Action, InputState> states;

  std::vector<InputContext> contextStack;

  int listenerId=0;

    std::unordered_map<
    Action, 
    std::unordered_map<
      InputEventType, 
      std::vector<ListenerCallback>
      >
    >listeners;

  
};
