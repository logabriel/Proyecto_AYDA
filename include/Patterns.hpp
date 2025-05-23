#pragma once
#include "Constraint3D.hpp"
#include "Visualization.hpp"

#pragma region Example 1 Walls
#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define CORNER 3

// Patrón 0: Empty (vacío)
Constraint3D emptyConstraints(
    {EMPTY},              // Above
    {EMPTY, WALL, FLOOR}, // Below
    {EMPTY, WALL, FLOOR}, // Norte
    {EMPTY, WALL, FLOOR}, // Este
    {EMPTY, WALL, FLOOR}, // Sur
    {EMPTY, WALL, FLOOR}  // Oeste
);
// Patrón 1: Floor (suelo)
Constraint3D floorConstraints(
    {EMPTY, FLOOR, WALL}, // Above
    {FLOOR},              // Below
    {FLOOR, EMPTY},       // Norte
    {FLOOR, EMPTY},       // Este
    {FLOOR, EMPTY},       // Sur
    {FLOOR, EMPTY}        // Oeste
);
// Patrón 2: Wall (muro)
Constraint3D wallConstraints(
    {WALL},        // Above
    {WALL, FLOOR}, // Below
    {WALL},        // Norte
    {EMPTY},       // Este
    {WALL},        // Sur
    {EMPTY}        // Oeste
);
#pragma endregion

#pragma region Example 2 Terreno
#define AIR 0
#define WATER 1
#define EARTH 2
#define SAND 3
#define GRASS 4

// example 2 : Terreno

// Patrón 0: aire (vacío)
Constraint3D airConstraints(
    {AIR},                     // Above
    {AIR, WATER, EARTH, SAND}, // Below
    {AIR},                     // Norte
    {AIR},                     // Este
    {AIR},                     // Sur
    {AIR}                      // Oeste
);
// Patrón 1: water (agua)
Constraint3D waterConstraints(
    {WATER, AIR},             // Above
    {WATER, EARTH, SAND},     // Below
    {WATER, SAND, /*EARTH*/}, // Norte
    {WATER, SAND, /*EARTH*/}, // Este
    {WATER, SAND, /*EARTH*/}, // Sur
    {WATER, SAND, /*EARTH*/}  // Oeste
);
// Patrón 2: earth (tierra)
Constraint3D earthConstraints(
    {AIR, WATER, GRASS},  // Above
    {EARTH},              // Below
    {EARTH, SAND, GRASS}, // Norte
    {EARTH, SAND, GRASS}, // Este
    {EARTH, SAND, GRASS}, // Sur
    {EARTH, SAND, GRASS}  // Oeste
);
// Patrón 3: sand (arena)
Constraint3D sandConstraints(
    {AIR, SAND, WATER},   // Above
    {SAND, EARTH},        // Below
    {SAND, EARTH, WATER}, // Norte
    {SAND, EARTH, WATER}, // Este
    {SAND, EARTH, WATER}, // Sur
    {SAND, EARTH, WATER}  // Oeste
);

Constraint3D grassConstraints(
    {AIR},               // Above
    {GRASS, EARTH},      // Below
    {EARTH, GRASS, AIR}, // Norte
    {EARTH, GRASS, AIR}, // Este
    {EARTH, GRASS, AIR}, // Sur
    {EARTH, GRASS, AIR}  // Oeste
);

std::vector<Color> terrain_colors = {
    // AIR 0
    (Color){0, 121, 241, 90}, // WATER 1
    BROWN,                    // EARTH 2
    BEIGE,                    // SAND 3
    GREEN,                    // GRASS 4
};
#pragma endregion

#pragma region Example 3 Roads

#define AIR 0
#define ROAD_GROUND 1
#define ROAD_NS 2
#define ROAD_EW 3
#define ROAD_NE 4
#define ROAD_NW 5
#define ROAD_SE 6
#define ROAD_SW 7
#define CROSS_ROAD 8
#define BUILDING_N 9
#define BUILDING_S 10
#define BUILDING_E 11
#define BUILDING_W 12

std::vector<Color> roads_colors = {
    // AIR
    GREEN,     // ROAD_GROUND
    GRAY,      // ROAD_NS
    DARKGRAY,  // ROAD_EW
    LIGHTGRAY, // CROSS_ROAD
    GOLD,      // BUILDING_E
    ORANGE,    // ROAD_NE
    PINK,      // ROAD_NW
    RED,
    MAROON,
    GREEN,
    LIME,
    BLUE,
    SKYBLUE,
};

Constraint3D roads_airConstraints(
    {AIR}, // Above
    {AIR, ROAD_GROUND,
     ROAD_NS,
     ROAD_EW,
     ROAD_NE,
     ROAD_NW,
     ROAD_SE,
     ROAD_SW,
     BUILDING_N,
     BUILDING_S,
     BUILDING_E,
     BUILDING_W}, // Below
    {AIR, ROAD_GROUND,
     BUILDING_N,
     BUILDING_S,
     BUILDING_E,
     BUILDING_W}, // Norte
    {AIR, ROAD_GROUND,
     BUILDING_N,
     BUILDING_S,
     BUILDING_E,
     BUILDING_W}, // Este
    {AIR, ROAD_GROUND,
     BUILDING_N,
     BUILDING_S,
     BUILDING_E,
     BUILDING_W}, // Sur
    {AIR, ROAD_GROUND,
     BUILDING_N,
     BUILDING_S,
     BUILDING_E,
     BUILDING_W} // Oeste
);
// Patrón 1: Road Ground
Constraint3D GroundConstraints(
    {AIR},                       // Above
    {ROAD_GROUND},               // Below
    {AIR, ROAD_GROUND, ROAD_EW}, // Norte
    {AIR, ROAD_GROUND, ROAD_NS}, // Este
    {AIR, ROAD_GROUND, ROAD_EW}, // Sur
    {AIR, ROAD_GROUND, ROAD_NS}  // Oeste
);

Constraint3D Road_NSConstraints(
    {AIR},         // Above
    {ROAD_GROUND}, // Below
    {ROAD_NS},     // Norte
    {ROAD_GROUND}, // Este
    {ROAD_NS},     // Sur
    {ROAD_GROUND}  // Oeste
);

Constraint3D CrossRoadConstraints(
    {AIR},         // Above
    {ROAD_GROUND}, // Below
    {ROAD_NS},     // Norte
    {ROAD_EW},     // Este
    {ROAD_NS},     // Sur
    {ROAD_EW}      // Oeste
);

Constraint3D Road_EWConstraints(
    {AIR},         // Above
    {ROAD_GROUND}, // Below
    {ROAD_GROUND}, // Norte
    {ROAD_EW},     // Este
    {ROAD_GROUND}, // Sur
    {ROAD_EW}      // Oeste
);

Constraint3D Building_EConstraints(
    {BUILDING_E, AIR},         // Above
    {ROAD_GROUND, BUILDING_E}, // Below
    {ROAD_GROUND, AIR},        // Norte
    {ROAD_GROUND, AIR},        // Este
    {ROAD_GROUND, AIR},        // Sur
    {ROAD_NS}                  // Oeste
);

Constraint3D Road_NEConstraints(
    {AIR},              // Above
    {ROAD_GROUND},      // Below
    {ROAD_NS},          // Norte
    {ROAD_EW, ROAD_NW}, // Este
    {ROAD_GROUND},      // Sur
    {ROAD_GROUND}       // Oeste
);

Constraint3D Road_NWConstraints(
    {AIR},             // Above
    {ROAD_GROUND},     // Below
    {ROAD_NS},         // Norte
    {ROAD_GROUND},     // Este
    {ROAD_GROUND},     // Sur
    {ROAD_EW, ROAD_NE} // Oeste
);

std::vector<std::vector<std::vector<std::set<unsigned int>>>> RoadsExample =
    {
        {{{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}}},

        {{{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}}},

        {{{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}}},

        {{{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}}},

        {{{ROAD_GROUND}, {ROAD_NS}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}},
         {{ROAD_GROUND}, {ROAD_GROUND}, {AIR}, {AIR}, {AIR}}},
};

#pragma endregion Example 3 Roads
////
using PatternVec = std::vector<Object3D>;
using WeightsVec = std::vector<double>;
using ConstraintVec = std::vector<Constraint3D>;
std::tuple<PatternVec, WeightsVec> build_wfc_rules(std::vector<int> pattern_ids, WeightsVec pattern_weights, ConstraintVec pattern_constraints)
{
    PatternVec patterns;
    for (size_t i = 0; i < pattern_ids.size(); ++i)
    {
        patterns.emplace_back(pattern_ids[i], pattern_weights[i], pattern_constraints[i]);
    }
    return std::make_tuple(patterns, pattern_weights);
}