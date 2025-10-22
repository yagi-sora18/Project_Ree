#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../Object/Player/Player.h"
#include "../Object/Platform/Platform.h"
#include "../Object/Item/Coin.h"
#include "../Object/Wall/Wall.h"


inline void LoadMapFromCSV(
	const std::string& filename,
	std::vector<Player>& player,
	std::vector<Platform>& platforms,
	std::vector<Coin>& coins,
	std::vector<Wall>& walls,
	//int tile_size = 50)
	int tile_size = 50,
	int* out_map_w_px = nullptr,
	int* out_map_h_px = nullptr)

{
	std::ifstream ifs(filename);
	if (!ifs) return;
	//std::string line; int row = 0;
	std::string line; int row = 0; int max_cols = 0;
	while (std::getline(ifs, line)) {
		//for (int col = 0; col < (int)line.size(); ++col) {
		max_cols = std::max<int>(max_cols, (int)line.size());
		for (int col = 0; col < (int)line.size(); ++col) {
			char ch = line[col];
			float x = col * (float)tile_size;
			float y = row * (float)tile_size;
			switch (ch) {
			case 'p': player.emplace_back(x, y, (float)tile_size, (float)tile_size); break;
			case '#': platforms.emplace_back(x, y + (float)tile_size * 0.8f, (float)tile_size, (float)tile_size * 0.2f); break; // ”–‚¢‘«ê
			case 'o': coins.emplace_back(x + (float)tile_size * 0.25f, y + (float)tile_size * 0.25f, (float)tile_size * 0.5f, (float)tile_size * 0.5f); break;
			case 'q': walls.emplace_back(x, y, (float)tile_size, (float)tile_size); break;
			default: break;
			}
		}
		++row;
	}

	if (out_map_w_px) *out_map_w_px = max_cols * tile_size;
	if (out_map_h_px) *out_map_h_px = row * tile_size;

}