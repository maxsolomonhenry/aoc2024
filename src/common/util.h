#pragma once

#include <string>
#include <vector>

namespace util {
    std::vector<std::string> read(const std::string &fpath);
    std::vector<int> parseIntegers(const std::string &line, const char delimiter);

    template <typename T>
    bool contains(std::vector<T> list, T value){
        return std::find(list.begin(), list.end(), value) != list.end();
    }
}