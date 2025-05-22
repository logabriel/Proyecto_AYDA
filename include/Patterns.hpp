#pragma once
#include "Constraint3D.hpp"
#include "Visualization.hpp"
#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define CORNER 3

// 1. Definir patrones 3D y sus restricciones
// std::vector<Object3D> patterns;

// Patrón 0: Empty (vacío)
Constraint3D emptyConstraints(
    {EMPTY},                   // Above
    {EMPTY, WALL, /*CORNER*/}, // Below
    {EMPTY, WALL, /*CORNER*/}, // Norte
    {EMPTY, WALL, /*CORNER*/}, // Este
    {EMPTY, WALL, /*CORNER*/}, // Sur
    {EMPTY, WALL, /*CORNER*/}  // Oeste
);
// Patrón 1: Floor (suelo)
Constraint3D floorConstraints(
    {EMPTY, FLOOR, WALL}, // Above
    {/*EMPTY,*/ FLOOR},   // Below
    {FLOOR},              // Norte
    {FLOOR},              // Este
    {FLOOR},              // Sur
    {FLOOR}               // Oeste
);
// Patrón 2: Wall (muro)
Constraint3D wallConstraints(
    {EMPTY, WALL}, // Above
    {FLOOR, WALL}, // Below
    {EMPTY, WALL}, // Norte
    {EMPTY, WALL}, // Este
    {EMPTY, WALL}, // Sur
    {EMPTY, WALL}  // Oeste
);

#define AIR 0
#define WATER 1
#define EARTH 2
#define SAND 3

// example 2
// Definición de tipos de bloques

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
    {WATER, AIR},         // Above
    {EARTH, SAND}, // Below
    {WATER, SAND, EARTH},        // Norte
    {WATER, SAND, EARTH},        // Este
    {WATER, SAND, EARTH},        // Sur
    {WATER, SAND, EARTH}         // Oeste
);
// Patrón 2: earth (tierra)
Constraint3D earthConstraints(
    {AIR, SAND, WATER},       // Above
    {EARTH},                   // Below
    {EARTH, SAND, WATER}, // Norte
    {EARTH, SAND, WATER}, // Este
    {EARTH, SAND, WATER}, // Sur
    {EARTH, SAND, WATER}  // Oeste
);
// Patrón 3: sand (arena)
Constraint3D sandConstraints(
    {AIR, SAND, WATER},        // Above
    {SAND, EARTH},             // Below
    {SAND, EARTH, WATER}, // Norte
    {SAND, EARTH, WATER}, // Este
    {SAND, EARTH, WATER}, // Sur
    {SAND, EARTH, WATER}  // Oeste
);

std::vector<Color> terrain_colors = {
    // AIR 0
    (Color){0, 121, 241, 50}, // WATER 1
    BROWN,                    // EARTH 2
    BEIGE                     // SAND 3
};