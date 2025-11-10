#include "scenes/TransitionScene.hpp"
#include <algorithm>

void TransitionScene::Init(){
    state = TransitionState::FadeIn;
    timer = 0.0f;
    t = 0.0f;
}

void TransitionScene::Update(float dt){
    switch (state)
    {
    case TransitionState::FadeIn:
        timer+=dt;
        t = std::clamp(timer/transitionDuration, 0.0f, 1.0f);
        alpha = Lerp(0.0f, 1.0f, t);
        if(t >= 1.0f){
            state=TransitionState::Hold;
            timer = 0.0f;
        }
        break;
    
    case TransitionState::Hold:
        timer+=dt;
        if(timer>holdTime){
            state = TransitionState::FadeOut;
            timer = 0.0f;
        }
        break;

    case TransitionState::FadeOut:
        timer+=dt;
        t = std::clamp(timer/transitionDuration, 0.0f, 1.0f);
        alpha = Lerp(1.0f, 0.0f, t);
        if(t >= 1.0f){
            state = TransitionState::Done;
            timer = 0.0f;
            if(onDone) onDone();
        }
        break;

    case TransitionState::Done:
        //idle
        break;
    }
}

void TransitionScene::Draw() const{
    DrawRectangle(
        0, 0, 
        GetScreenWidth(), GetScreenHeight(),
        Fade(BLACK,alpha)
    );
}