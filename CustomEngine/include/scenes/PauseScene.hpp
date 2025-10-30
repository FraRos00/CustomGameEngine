#pragma once
#include "core/Scene.hpp"
#include "utils/Text.hpp"
#include <raylib.h>
#include <memory>

class PauseScene : public Scene {
public:
    PauseScene() : Scene("PauseScene") {};
    
    void Init() override;
    void Update(float dt) override;
    void Draw() const override;
    void HandleInputs() override {};
    
    ~PauseScene() override = default;
    private:
    std::unique_ptr<Text> pauseText = nullptr;
};