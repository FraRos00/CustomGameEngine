#include "ui/UiManager.hpp"
#include <algorithm>

void UiManager::Update(float dt){
    for(const auto &el : uiElements){
        //update only when visible?
        el->Update(dt);
    }
}

void UiManager::Draw()const{
    for(const auto &el : uiElements){
        if(el->IsVisible())
            el->Draw();
    }
}

void UiManager::SortByZIndex(){
    std::sort(uiElements.begin(),uiElements.end(),
        [](const auto &a, const auto &b){
            return a->GetZOrder() < b->GetZOrder();
        }
    );
}