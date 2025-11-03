#pragma once
#include "core/InputManager.hpp"

class InputSubscription {
    public:
    InputSubscription(int id) : id(id){};

    InputSubscription(const InputSubscription& other) = delete;
    InputSubscription& operator=(const InputSubscription& other) = delete;


    InputSubscription(InputSubscription&& other) noexcept : id(other.id){
        other.id=-1;
    }

    InputSubscription& operator=(InputSubscription&& other) noexcept{
        if(this!=&other){
            if(id!=-1) InputManager::GetInstance().UnsubscribeListener(id);
            id = other.id;
            other.id = -1;
        }
        return *this;
    }


    ~InputSubscription() {
        if (id != -1) InputManager::GetInstance().UnsubscribeListener(id);
    }
    
    private:
    int id=-1;
};
