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
// Patrón 3: Corner (esquina)
// Constraint3D cornerConstraints(
//     {EMPTY},                      // Above
//     {FLOOR},                      // Below
//     {EMPTY, FLOOR, WALL, /*CORNER*/}, // Norte
//     {EMPTY, FLOOR, WALL, /*CORNER*/}, // Este
//     {EMPTY, FLOOR, WALL, /*CORNER*/}, // Sur
//     {EMPTY, FLOOR, WALL, /*CORNER*/}  // Oeste
// );
// patterns.emplace_back(3, 1.0, cornerConstraints);

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
    {EARTH, SAND, WATER}, // Below
    {WATER, SAND},        // Norte
    {WATER, SAND},        // Este
    {WATER, SAND},        // Sur
    {WATER, SAND}         // Oeste
);
// Patrón 2: earth (tierra)
Constraint3D earthConstraints(
    {AIR, EARTH, WATER},       // Above
    {EARTH},                   // Below
    {EARTH, SAND, AIR, WATER}, // Norte
    {EARTH, SAND, AIR, WATER}, // Este
    {EARTH, SAND, AIR, WATER}, // Sur
    {EARTH, SAND, AIR, WATER}  // Oeste
);
// Patrón 3: sand (arena)
Constraint3D sandConstraints(
    {AIR, SAND, WATER},        // Above
    {SAND, EARTH},             // Below
    {SAND, EARTH, WATER, AIR}, // Norte
    {SAND, EARTH, WATER, AIR}, // Este
    {SAND, EARTH, WATER, AIR}, // Sur
    {SAND, EARTH, WATER, AIR}  // Oeste
);
std::vector<Color> terrain_colors = {
    // AIR 0
    (Color){0, 121, 241, 50}, // WATER 1
    BROWN,                    // EARTH 2
    BEIGE                     // SAND 3
};