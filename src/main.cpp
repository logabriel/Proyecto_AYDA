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

Wfc3D walls_example(int x, int y, int z, int seed)
{

    auto [walls_patterns, walls_weights] = build_wfc_rules(
        {EMPTY, FLOOR, WALL},
        {1.0, 1.5, 2.0},
        {emptyConstraints, floorConstraints, wallConstraints});

    // Crear generador 3D (5x5x5)
    Wfc3D wfc(walls_patterns, walls_weights, {x, y, z}, seed);
    wfc.createBaseLayer(FLOOR);
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

Wfc3D terrain_example(int x, int y, int z, int seed)
{

    auto [patterns_terr, weights_terr] = build_wfc_rules(
        {AIR, WATER, EARTH, SAND},
        {1.0, 1.0, 1.0, 1.0},
        {airConstraints, waterConstraints, earthConstraints, sandConstraints});
    // Wfc3D wfc(patterns, weights, {10, 10, 5}, 123);
    Wfc3D wfc(patterns_terr, weights_terr, {x, y, z}, seed);
    wfc.createBaseLayer(EARTH);

    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
        // wfc.printResult();
    }

    return wfc;
}

Wfc3D roads_example(int x, int y, int z, int seed)
{
    auto [patterns_roads, weights_roads] = build_wfc_rules(
        {AIR,
         ROAD_GROUND,
         ROAD_NS,
         ROAD_EW,
         CROSS_ROAD,
         BUILDING_E,
         ROAD_NE,
         ROAD_NW},
        {0.1, 0.5, 2.0, 2.0, 1.0, 2.0, 2.0, 2.0},
        {roads_airConstraints,
         GroundConstraints,
         Road_NSConstraints,
         Road_EWConstraints,
         CrossRoadConstraints,
         Building_EConstraints,
         Road_NEConstraints,
         Road_NWConstraints});
    // Wfc3D wfc(patterns, weights, {10, 10, 5}, 123);
    Wfc3D wfc(patterns_roads, weights_roads, {x, y, z}, seed);
    wfc.createBaseLayer(ROAD_GROUND);

    if (wfc.executeWfc3D())
    {
        std::cout << "Generación 3D completada con éxito!\n";
        wfc.printResult();
    }
    else
    {
        std::cout << "La generación 3D falló debido a contradicciones.\n";
        // wfc.printResult();
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

        // Wfc3D wfc(patterns, weights, {x, y, z}, seed);

        auto walls_wfc = walls_example(x, y, z, seed);
        auto terrain__wfc = terrain_example(x, y, z, seed);
        auto roads__wfc = roads_example(x, y, z, seed);

        display_scene_from_vector(walls_wfc.getRenderVector(), roads_colors);
        display_scene_from_vector(terrain__wfc.getRenderVector(), terrain_colors);
        display_scene_from_vector(roads__wfc.getRenderVector(), roads_colors);
        // display_scene_from_matrix( , roads_colors);
        // display_scene_from_matrix( , terrain_colors);
        // display_scene_from_matrix( , roads_colors);

        // if (wfc.executeWfc3D())
        // {
        //     std::cout << "Generación 3D completada con éxito!\n";
        //     wfc.printResult();
        // }
        // else
        // {
        //     std::cout << "La generación 3D falló debido a contradicciones.\n";
        //     wfc.printResult();
        // }
        // display_scene_from_matrix(wfc);
    }
    if (argc != 5)
    {
        std::cout << "\n\t esperando:\t <x> <y> <z> <seed>\n"
                  << std::endl;
        return 1;
    }

    return 0;
}