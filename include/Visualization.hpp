#pragma once
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "Wfc3D.hpp"

void display_scene_from_matrix(Wfc3D wfc3d, std::vector<Color> display_colors);
void display_scene_from_matrix(std::vector<std::vector<std::vector<std::set<unsigned int>>>> wfc3d, std::vector<Color> display_colors);