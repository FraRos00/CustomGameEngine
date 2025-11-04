#include <string>
#include <unordered_map>
namespace global {

std::unordered_map<std::string, float> fontSizes{{"h1", 60.0f}, {"h2", 50.0f},
                                                 {"h3", 45.0f}, {"h4", 35.0f},
                                                 {"h5", 24.0f}, {"p", 15.0f}};

bool DEBUG = false;
}