#include <vector>
#include <tuple>
#include <iostream>
#include "Wfc3D.hpp"
#include "Visualization.hpp"

#include "Patterns.hpp"

void printWeights(const std::vector<double> &weights)
{
    std::cout << "Pesos de los patrones:\n";
    for (size_t i = 0; i < weights.size(); ++i)
    {
        std::cout << "weights[" << i << "] = " << weights[i] << "\n";
    }
    std::cout << "--------------------------\n";
}

int example_wfc()
{
    std::vector<Object3D> patterns;
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

Wfc3D terrain_example()
{
    std::vector<Object3D> patterns;
    patterns.emplace_back(AIR, 1.0, airConstraints);
    patterns.emplace_back(WATER, 1.0, waterConstraints);
    patterns.emplace_back(EARTH, 1.0, earthConstraints);
    patterns.emplace_back(SAND, 1.9, sandConstraints);

    std::vector<double> weights;
    for (const auto &p : patterns)
    {
        weights.push_back(p.weight);
    }

    Wfc3D wfc(patterns, weights, {50, 50, 3}, 123);
    wfc.createBaseLayer(EARTH);

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

Wfc3D generate_and_print_wfc(int x, int y, int z, int seed, std::vector<double> weights)
{
    std::vector<Object3D> patterns;
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
    /*
    #pragma region Patterns/Weights Setup
        std::vector<Object3D> patterns;
        patterns.emplace_back(0, 1.0, emptyConstraints);
        patterns.emplace_back(1, 1.0, floorConstraints);
        patterns.emplace_back(2, 5.5, wallConstraints);

        std::vector<double> weights;
        for (const auto &p : patterns)
        {
            weights.push_back(p.weight);
        }
    #pragma endregion

        if (argc == 1)
        {
            std::cout << "No se han pasado argumentos." << std::endl;
        }
        if (argc == 5)
        {
            int x = std::stoi(argv[1]);
            int y = std::stoi(argv[2]);
            int z = std::stoi(argv[3]);
            int seed = std::stoi(argv[4]);
            std::cout << "Generando 3D con dimensiones: " << x << "x" << y << "x" << z << "\n\tSeed: " << seed << std::endl;

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
            display_scene_from_matrix(wfc);
        }
        if (argc != 5)
        {
            std::cout << "\n\t esperando:\t <x> <y> <z> <seed>\n"
                      << std::endl;
            return 1;
        }

        */
    //    example_wfc();
    // terrain_example();

    display_scene_from_matrix(terrain_example(), terrain_colors);

    return 0;
}