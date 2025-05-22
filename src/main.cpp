#include "Wfc3D.hpp"
#include <vector>
#include <tuple>
#include <iostream>

void printWeights(const std::vector<double> &weights)
{
    std::cout << "Pesos de los patrones:\n";
    for (size_t i = 0; i < weights.size(); ++i)
    {
        std::cout << "weights[" << i << "] = " << weights[i] << "\n";
    }
    std::cout << "--------------------------\n";
}

// Temp, for Readability of constraints below
#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define CORNER 3

// 1. Definir patrones 3D y sus restricciones
std::vector<Object3D> patterns;

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

int example_wfc()
{
    patterns.emplace_back(0, 1.0, emptyConstraints);
    patterns.emplace_back(1, 1.5, floorConstraints);
    patterns.emplace_back(2, 1.0, wallConstraints);

    std::vector<double> weights;
    for (const auto &p : patterns)
    {
        weights.push_back(p.weight);
    }
    // Crear generador 3D (5x5x5)
    Wfc3D wfc(patterns, weights, {10, 10, 10}, 500);

    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
        wfc.printResult();
    }

    return 0;
}

// example 2 
// Definición de tipos de bloques
#define AIR 0
#define WATER 1
#define EARTH 2
#define SAND 3

// Patrón 0: aire (vacío)
Constraint3D airConstraints(
    {AIR},            // Above 
    {AIR, WATER, EARTH, SAND}, // Below
    {AIR,},     // Norte
    {AIR,},     // Este
    {AIR,},     // Sur
    {AIR,}     // Oeste
);
// Patrón 1: water (agua)
Constraint3D waterConstraints(
    {WATER, AIR},     // Above 
    {EARTH, SAND, WATER},    // Below
    {WATER, SAND}, // Norte
    {WATER, SAND}, // Este
    {WATER, SAND}, // Sur
    {WATER, SAND} // Oeste
);
// Patrón 2: earth (tierra)
Constraint3D earthConstraints(
    {AIR, EARTH},     // Above 
    {EARTH,},    // Below 
    {EARTH, SAND, AIR}, // Norte
    {EARTH, SAND, AIR}, // Este
    {EARTH, SAND, AIR}, // Sur
    {EARTH, SAND, AIR}  // Oeste
);
// Patrón 3: sand (arena)
Constraint3D sandConstraints(
    {AIR, SAND},     // Above 
    {SAND, EARTH},    // Below 
    {SAND, EARTH, WATER, AIR}, // Norte
    {SAND, EARTH, WATER, AIR}, // Este
    {SAND, EARTH, WATER, AIR}, // Sur
    {SAND, EARTH, WATER, AIR}  // Oeste
);

int example2_wfc()
{
    std::vector<Object3D> patterns;
    patterns.emplace_back(AIR, 0.8, airConstraints);     
    patterns.emplace_back(WATER, 1.2, waterConstraints); 
    patterns.emplace_back(EARTH, 1.0, earthConstraints); 
    patterns.emplace_back(SAND, 1.0, sandConstraints);  

    std::vector<double> weights;
    for (const auto &p : patterns)
    {
        weights.push_back(p.weight);
    }

    Wfc3D wfc(patterns, weights, {4, 4, 4}, 15473);
    wfc.createBaseLayer(2);
    
    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
        wfc.printResult();
    }

    return 0;
}
// fin example 2

Wfc3D generate_and_print_wfc(int x, int y, int z, int seed, std::vector<double> weights)
{
    Wfc3D wfc(patterns, weights, {x, y, z}, seed);

    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
        wfc.printResult();
    }
    return wfc;
}

int main(int argc, const char **argv)
{
// #pragma region Patterns Setup
//     patterns.emplace_back(0, 1, emptyConstraints);
//     patterns.emplace_back(1, 1.5, floorConstraints);
//     patterns.emplace_back(2, 0.4, wallConstraints);
//     std::vector<double> weights;
//     for (const auto &p : patterns)
//     {
//         weights.push_back(p.weight);
//     }
// #pragma endregion
//     if (argc == 1)
//     {
//         std::cout << "No se han pasado argumentos." << std::endl;
//     }
//     if (argc == 5)
//     {
//         int x = std::stoi(argv[1]);
//         int y = std::stoi(argv[2]);
//         int z = std::stoi(argv[3]);
//         int seed = std::stoi(argv[4]);
//         std::cout << "Generando 3D con dimensiones: " << x << "x" << y << "x" << z << "\n\tSeed: " << seed << std::endl;
//         Wfc3D wfc_result = generate_and_print_wfc(x, y, z, seed, weights);
//     }
//     if (argc != 5)
//     {
//         std::cout << "\n\t esperando:\t <x> <y> <z> <seed>\n"
//                   << std::endl;
//         return 1;
//     }

    //example2_wfc();
    example_wfc();

    return 0;
}