#pragma once
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "Wfc3D.hpp"
// std::vector<Color> colors = {LIGHTGRAY,
//                              GRAY,
//                              DARKGRAY,
//                              YELLOW,
//                              GOLD,
//                              ORANGE,
//                              PINK,
//                              RED,
//                              MAROON,
//                              GREEN,
//                              LIME,
//                              DARKGREEN,
//                              SKYBLUE,
//                              BLUE,
//                              DARKBLUE,
//                              PURPLE,
//                              VIOLET,
//                              DARKPURPLE,
//                              BEIGE,
//                              BROWN,
//                              DARKBROWN,
//                              BLACK,
//                              BLANK,
//                              MAGENTA,
//                              RAYWHITE};

void display_scene_from_matrix(Wfc3D wfc3d, std::vector<Color> display_colors);