#include "util.h"

#include <fstream>
#include <iostream>

namespace util {
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
}
