#pragma once
#include <unordered_map>
#include <string>
#include <vector>



namespace global {
    extern std::unordered_map<std::string, float> fontSizes;

    template <typename T, typename Pred>
    void unordered_removeif(std::vector<T> &vec, Pred pred) {
    for (size_t i = 0; i < vec.size();) {
        if (pred(vec[i])) {
        vec[i] = std::move(vec.back());
        vec.pop_back();
        } else {
        i++;
        }
    }
    }
    

}
