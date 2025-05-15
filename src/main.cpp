#include "Wfc3D.hpp"
#include <vector>
#include <tuple>
#include <iostream>

void printWeights(const std::vector<double>& weights) {
    std::cout << "Pesos de los patrones:\n";
    for (size_t i = 0; i < weights.size(); ++i) {
        std::cout << "weights[" << i << "] = " << weights[i] << "\n";
    }
    std::cout << "--------------------------\n";
}

int main()
{
    // 1. Definir patrones 3D y sus restricciones
    std::vector<Object3D> patterns;

    // Patrón 0: Empty (vacío)
    Constraint3D emptyConstraints(
        {0}, {0}, {0}, {0}, {0}, {0}  // Solo se conecta consigo mismo
    );
    patterns.emplace_back(0, 1.0, emptyConstraints);

    // Patrón 1: Floor (suelo)
    Constraint3D floorConstraints(
        {0, 2},    // Above: empty o wall
        {0},       // Below: solo empty
        {0, 1, 2}, // Norte: empty, floor, wall
        {0, 1, 2}, // Este: empty, floor, wall
        {0, 1, 2}, // Sur: empty, floor, wall
        {0, 1, 2}  // Oeste: empty, floor, wall
    );
    patterns.emplace_back(1, 2.0, floorConstraints);

    // Patrón 2: Wall (muro)
    Constraint3D wallConstraints(
        {0},       // Above: solo empty
        {1},       // Below: solo floor
        {0, 1, 2}, // Norte: empty, floor, wall
        {0, 1, 2}, // Este: empty, floor, wall
        {0, 1, 2}, // Sur: empty, floor, wall
        {0, 1, 2}  // Oeste: empty, floor, wall
    );
    patterns.emplace_back(2, 1.5, wallConstraints);

    // Patrón 3: Corner (esquina)
    Constraint3D cornerConstraints(
        {0},             // Above: solo empty
        {1},             // Below: solo floor
        {0, 1, 2, 3},   // Norte: empty, floor, wall, corner
        {0, 1, 2, 3},   // Este: empty, floor, wall, corner
        {0, 1, 2, 3},   // Sur: empty, floor, wall, corner
        {0, 1, 2, 3}    // Oeste: empty, floor, wall, corner
    );
    patterns.emplace_back(3, 1.0, cornerConstraints);

    std::vector<double> weights;
    for (const auto &p : patterns)
    {
        weights.push_back(p.weight);
    }

    // Crear generador 3D (5x5x5)
    Wfc3D wfc(patterns, weights, {5, 5, 5}, 47);

    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
    }

    return 0;
}