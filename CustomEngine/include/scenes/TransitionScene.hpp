#include <raylib.h>
#include <raymath.h>
#include <utility>

#include "core/Scene.hpp"


enum class TransitionState{ FadeIn, Hold, FadeOut, Done};

class TransitionScene : public Scene {
    public:
        template<typename F>
        TransitionScene(F&& onDone) 
        : Scene("TransitionScene"), onDone(std::forward<F>(onDone)){};

        void Init() override;
        void Update(float dt) override;
        void Draw() const override;



    private:
    float alpha = 0.0f;
    float transitionDuration = 1.0f;
    float holdTime = 0.5f;
    float timer = 0.0f;
    float t = 0.0f; //clamped timer
    TransitionState state = TransitionState::FadeIn;
    std::function<void()> onDone;
};