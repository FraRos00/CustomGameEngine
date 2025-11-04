#pragma once
#include <vector>
#include <memory>
#include "ui/UiElement.hpp"

class UiManager{
    public:
        template<typename T, typename... Args>
        T* CreateElement(Args&&... args){
            auto element = std::make_unique<T>(std::forward<Args>(args)...);
            T* ptr = element.get();
            uiElements.emplace_back(std::move(element));
            SortByZIndex();
            return ptr;
        }

        void Update(float dt);
        void Draw()const;
        

    private:
        void SortByZIndex();

        std::vector<std::unique_ptr<UiElement>> uiElements;
};