#include "util.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace util {

    int ctoi(const char c) {
        if (std::isdigit(c))
            return c - '0';
        return -1;
    }

    std::vector<std::string> read(const std::string &fpath) {
        
        std::ifstream file(fpath);
        std::vector<std::string> lines;
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error opening file.\n";
            return lines;
        }

        while (std::getline(file, line))
            lines.push_back(line);

        
        file.close();

        return lines;
    }

    std::vector<int> parseIntegers(const std::string &line, const char delimiter) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<int> buffer;

        while (std::getline(ss, temp, delimiter))
            buffer.push_back(std::stoi(temp));

        return buffer;
    }

        std::vector<long> parseLongs(const std::string &line, const char delimiter) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<long> buffer;

        while (std::getline(ss, temp, delimiter))
            buffer.push_back(std::stol(temp));

        return buffer;
    }
}
