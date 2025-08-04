#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"  // Coinクラスのパス

void LoadMapFromCSV(
    const std::string& filename,
    std::vector<Platform>& platforms,
    std::vector<Coin>& coins,
    int tile_size = 50)
{
    std::ifstream file(filename);
    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        for (int col = 0; col < line.size(); ++col) {
            char c = line[col];
            float x = col * tile_size;
            float y = row * tile_size;

            if (c == '#') {
                platforms.emplace_back(x, y, tile_size, tile_size / 5);
            }
            else if (c == 'o') {
                coins.emplace_back(x + tile_size / 2, y + tile_size / 2);
            }
        }
        ++row;
    }
}

