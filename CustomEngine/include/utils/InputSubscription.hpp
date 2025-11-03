#pragma once
#include "core/InputManager.hpp"

class InputSubscription {
    public:
    InputSubscription(int id) : id(id){};
    ~InputSubscription() {
        if (id != -1) InputManager::GetInstance().UnsubscribeListener(id);
    }
    
    private:
    int id;
};
