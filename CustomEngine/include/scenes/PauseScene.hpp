#pragma once
#include <raylib.h>
#include <memory>
#include "core/Scene.hpp"
#include "utils/Text.hpp"


class PauseScene : public Scene {
public:
    PauseScene() : Scene("PauseScene") {};
    
    void Init() override;
    void Update(float dt) override;
    void Draw() const override;
    
    ~PauseScene() override = default;
    private:
    std::unique_ptr<Text> pauseText = nullptr;

};