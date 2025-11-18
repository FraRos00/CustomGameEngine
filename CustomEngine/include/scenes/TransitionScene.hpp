#include <future>
#include <raylib.h>
#include <raymath.h>
#include <utility>

#include "core/Scene.hpp"

enum class TransitionState { FadeIn, Hold, FadeOut, Done };

class TransitionScene : public Scene {
public:
  template <typename F1, typename F2, typename F3, typename F4>
  TransitionScene(F1 &&onDone, F2 &&beforeTask, F3 &&asyncTask, F4 &&afterTask)
      : Scene("TransitionScene"), onDone(std::forward<F1>(onDone)),
        beforeTask(std::forward<F2>(beforeTask)),
        asyncTask(std::forward<F3>(asyncTask)),
        afterTask(std::forward<F4>(afterTask)){};

  void Init() override;
  void Update(float dt) override;
  void Draw() const override;

private:
  float alpha = 0.0f;
  float transitionDuration = 1.0f;
  float holdTime = 0.5f;
  float timer = 0.0f;
  float t = 0.0f; // clamped timer
  TransitionState state = TransitionState::FadeIn;
  std::function<void()> onDone;

  std::function<void()> beforeTask;
  std::function<void()> asyncTask;
  std::function<void()> afterTask;
  std::future<void> future;
  bool taskStarted = false;
};
