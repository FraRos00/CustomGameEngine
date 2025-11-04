#include "core/InputManager.hpp"
#include "globals/globals.hpp"
#include <raylib.h>

InputManager &InputManager::GetInstance() {
  static InputManager instance;
  return instance;
}

InputManager::InputManager() {
  bindings[InputContext::GameContext][Action::MoveRight] = KEY_D;
  bindings[InputContext::GameContext][Action::MoveLeft] = KEY_A;
  bindings[InputContext::GameContext][Action::MoveUp] = KEY_W;
  bindings[InputContext::GameContext][Action::MoveDown] = KEY_S;
  bindings[InputContext::GameContext][Action::Attack] = KEY_SPACE;
  bindings[InputContext::GameContext][Action::Pause] = KEY_ESCAPE;
  bindings[InputContext::GameContext][Action::OpenInventory] = KEY_I;
  bindings[InputContext::InventoryContext][Action::CloseInventory] = KEY_I;
  bindings[InputContext::PauseContext][Action::UnPause] = KEY_ESCAPE;
}

  void InputManager::SwitchContext(InputContext inputContext){
    contextStack.clear();
    PushContext(inputContext);
  }
  
  void InputManager::PushContext(InputContext inputContext){
    contextStack.push_back(inputContext);
  }

  void InputManager::PopContext(){
    if (!contextStack.empty())
    contextStack.pop_back();
  }


int InputManager::SubscribeListener(Action action, InputEventType eventType, std::function<void()> callback) {
  
  listeners[action][eventType].emplace_back(ListenerCallback{listenerId++, callback});
  return listenerId;

}

void InputManager::UnsubscribeListener(int id){

  for(auto &[_,listenersMap] : listeners){
    for(auto &[_,lcbv]:listenersMap){
    global::unordered_removeif(lcbv, [id](ListenerCallback &lcb){
      return lcb.listenerId == id;
    });
    }
  }

}

void InputManager::Update() {
  //for(const auto &context: contextStack)
  if(contextStack.empty()) return;
  const InputContext &context = contextStack.back(); //se modifico contextstack si invalida il riferimento

  for (auto &[action, key] : bindings[context]) {
    InputState &state = states[action];
    state.isPressed = IsKeyPressed(key);
    state.isHeld = IsKeyDown(key);
    state.isReleased = IsKeyReleased(key);


    auto itAction = listeners.find(action);
    if (itAction == listeners.end()) continue;

    if (state.isPressed)  Dispatch(action, InputEventType::Pressed);
    if (state.isHeld)     Dispatch(action, InputEventType::Held);
    if (state.isReleased) Dispatch(action, InputEventType::Released);

  }

}

void InputManager::Dispatch(Action action, InputEventType type) {
  //tecnicamente lo faccio gia fuori questo check
    auto itAction = listeners.find(action);
    if (itAction == listeners.end()) return;

    auto itType = itAction->second.find(type);
    if (itType == itAction->second.end()) return;
    for (auto &lcb : itType->second){
      lcb.callback();
    }
}

