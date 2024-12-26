#include "../common/util.h"

#include <unordered_map>
#include <iostream>
#include <deque>

using block = std::pair<int, int>;

std::deque<block> partOne(std::deque<block> memory);
std::deque<block> partTwo(std::deque<block> memory);

long long calculate(std::deque<block> memory) {
    long long checksum = 0;
    int blockNo = 0;
    for (int i = 0; i < memory.size(); i++) {

        const int& fileNo = memory[i].first;
        const int& nBlocks = memory[i].second;

        for (int j = 0; j < nBlocks; j++)
            checksum += (blockNo++) * (fileNo == -1 ? 0 : fileNo);
    }

    return checksum;
}

int main()
{

    const auto& lines = util::read("src/day09/input.txt");

    std::deque<block> memory;

    int fileNo = 0;
    for (int i = 0; i < lines[0].size(); i++)
    {
        if (i % 2 == 0)
            memory.push_back(block(fileNo++, util::ctoi(lines[0][i])));
        else
            memory.push_back(block(-1, util::ctoi(lines[0][i])));
    }

    std::cout << "checksum: " << calculate(partOne(memory)) << "\n";
    std::cout << "checksum: " << calculate(partTwo(memory)) << "\n";

    return 0;
}

std::deque<block> partTwo(std::deque<block> memory) {
    int pRead = memory.size() - 1;

    while (pRead > 0)
    {
        int fileNo = memory[pRead].first;

        if (fileNo == -1) {
            pRead -= 1;
            continue;
        }

        int nIncoming = memory[pRead].second;

        int pWrite = 0;
        for (int pWrite = 0; pWrite < pRead; pWrite++)
        {
            if (memory[pWrite].first != -1)
                continue;

            int nEmpty = memory[pWrite].second;
            if (nEmpty < nIncoming)
                continue;
            else if (nEmpty == nIncoming) {
                memory[pWrite].first = fileNo;
                memory[pRead].first = -1;
                break;
            } else if (nEmpty > nIncoming) {
                int nExtra = nEmpty - nIncoming;
                memory[pWrite] = block(fileNo, nIncoming);
                memory[pRead].first = -1;
                memory.insert(memory.begin() + pWrite + 1, block(-1, nExtra));

                // Advance to compensate for new item.
                pRead++;
                break;
            }

        }

        pRead--;
    }

    return memory;

}

std::deque<block> partOne(std::deque<block> memory) {
    int pWrite = 0;
    int pRead = memory.size() - 1;
    while (pWrite < pRead)
    {
        int fileNo = memory[pRead].first;
        int nIncoming = memory[pRead].second;

        // Skip empty space.
        if (fileNo == -1)
        {
            pRead--;
            continue;
        }

        // Ensure points to empty space.
        if (memory[pWrite].first != -1)
        {
            pWrite++;
            continue;
        }

        int nEmpty = memory[pWrite].second;

        if (nEmpty == nIncoming)
        {
            memory[pWrite] = block(fileNo, nIncoming);
            memory[pRead].first = -1;
        }
        else if (nEmpty < nIncoming)
        {
            memory[pWrite] = block(fileNo, nEmpty);
            memory[pRead].second -= nEmpty;
            // Add empty memory back at the end (note: may not be needed).
            memory.insert(memory.begin() + pRead + 1, block(-1, nEmpty));
        }
        else if (nEmpty > nIncoming)
        {
            int nExtra = nEmpty - nIncoming;
            memory[pWrite] = block(fileNo, nIncoming);
            memory[pRead].first = -1;
            memory.insert(memory.begin() + pWrite + 1, block(-1, nExtra));

            // Advance to compensate for new item.
            pRead++;
        }
    }

    return memory;
}
