#include "core/Engine.hpp"
// extern "C" int wl_get_output_scale();
#include <iostream>

int main(void) {
  int scale = 2;
  // int scale = wl_get_output_scale();
  // std::cout << "Output scale: " << scale << std::endl;
  Engine engine;

  engine.Init(scale);
  engine.Run();

  return 0;
}
