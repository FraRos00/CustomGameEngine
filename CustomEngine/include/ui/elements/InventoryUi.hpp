#pragma once
#include "core/InputManager.hpp"
#include "ui/UiElement.hpp"
#include <raylib.h>

class InventoryUi : public UiElement {
public:
  InventoryUi() {
    zIndex = 10;
    visible = false;
    InputManager::GetInstance().SubscribeListener(
        Action::CloseInventory, InputEventType::Pressed, [this]() {
          InputManager::GetInstance().PopContext();
          visible = false;
        });
  }
  void Update(float dt) override {};
  void Draw() const override {
    // 300 = screenwidth / 6.4
    // 400 1080 / 2.7
    DrawRectangle(50, 50, GetScreenWidth() / 6.4f, GetScreenHeight() / 2.7f,
                  Fade(BLUE, 0.5f));
  };

private:
};
