#pragma once
#include <raylib.h>
#include "ui/UiElement.hpp"
#include "core/InputManager.hpp"

class InventoryUi : public UiElement{
    public:
        InventoryUi(){
            zIndex=10;
            visible=false;
            InputManager::GetInstance().SubscribeListener(
                Action::CloseInventory,InputEventType::Pressed,
                [this](){
                    InputManager::GetInstance().PopContext();
                    visible = false;
                }
            );        
        }
        void Update(float dt) override{};
        void Draw()const override{
            DrawRectangle(50, 50, 300, 400, Fade(BLUE, 0.5f));};

    private:
            
};