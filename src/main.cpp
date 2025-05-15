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

int main()
{
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
    patterns.emplace_back(0, 1.0, emptyConstraints);

    // Patrón 1: Floor (suelo)
    Constraint3D floorConstraints(
        {EMPTY, FLOOR, WALL}, // Above
        {/*EMPTY,*/ FLOOR},   // Below
        {FLOOR},              // Norte
        {FLOOR},              // Este
        {FLOOR},              // Sur
        {FLOOR}               // Oeste
    );
    patterns.emplace_back(1, 1.0, floorConstraints);

    // Patrón 2: Wall (muro)
    Constraint3D wallConstraints(
        {EMPTY, WALL}, // Above
        {FLOOR, WALL}, // Below
        {EMPTY, WALL}, // Norte
        {EMPTY, WALL}, // Este
        {EMPTY, WALL}, // Sur
        {EMPTY, WALL}  // Oeste
    );
    patterns.emplace_back(2, 5.5, wallConstraints);

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