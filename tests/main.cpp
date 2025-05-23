#include <tuple>
#include <vector>
#include <iostream>
#include <assert.h>
#include "Wfc3D.hpp"
#include "Visualization.hpp"
#include "Patterns.hpp"
void test1Compatibility()
{
    // Configura patrones de prueba
    Object3D patternA(0, 1.0, Constraint3D({1}, {}, {}, {}, {}, {})); // A solo permite B arriba
    Object3D patternB(1, 1.0, Constraint3D({}, {0}, {}, {}, {}, {})); // B solo permite A abajo

    Wfc3D wfc({patternA, patternB}, {1.0, 1.0}, {1, 1, 1});

    // Pruebas de compatibilidad
    bool ab = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 0, 1);       // A con B arriba
    bool ba = wfc.is3DCompatible({0, 0, 1}, {0, 0, 0}, 1, 0);       // B con A abajo
    bool ba_wrong = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 1, 0); // B no puede estar arriba de A

    std::cout << "Compatibilidad A (abajo) con B (arriba): " << (ab ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Compatibilidad B (arriba) con A (abajo): " << (ba ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Compatibilidad B (abajo) con A (arriba): " << (ba_wrong ? "Compatible" : "No compatible") << std::endl;

    // assert(ab);
    // assert(ba);
    // assert(!ba_wrong);
}

void test2Compatibility()
{
    // Configura patrones de prueba
    Object3D patternA(0, 1.0, Constraint3D({1}, {1}, {1}, {1}, {1}, {1})); // A permite B en todas direcciones
    Object3D patternB(1, 1.0, Constraint3D({0}, {0}, {0}, {0}, {0}, {0})); // B permite A en todas direcciones

    Wfc3D wfc({patternA, patternB}, {1.0, 1.0}, {1, 1, 1});

    Coords3DInt c = {0, 0, 0};
    Coords3DInt up = {0, 0, 1};
    Coords3DInt down = {0, 0, -1};
    Coords3DInt north = {0, 1, 0};
    Coords3DInt south = {0, -1, 0};
    Coords3DInt east = {1, 0, 0};
    Coords3DInt west = {-1, 0, 0};

    std::cout << "Compatibilidad A con B en las seis direcciones:\n";
    std::cout << "Arriba (A abajo, B arriba): " << (wfc.is3DCompatible(c, up, 0, 1) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Abajo (A arriba, B abajo): " << (wfc.is3DCompatible(up, c, 0, 1) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Norte (A sur, B norte):    " << (wfc.is3DCompatible(c, north, 0, 1) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Sur (A norte, B sur):      " << (wfc.is3DCompatible(c, south, 0, 1) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Este (A oeste, B este):    " << (wfc.is3DCompatible(c, east, 0, 1) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Oeste (A este, B oeste):   " << (wfc.is3DCompatible(c, west, 0, 1) ? "Compatible" : "No compatible") << std::endl;

    std::cout << "\nCompatibilidad B con A en las seis direcciones:\n";
    std::cout << "Arriba (B abajo, A arriba): " << (wfc.is3DCompatible(c, up, 1, 0) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Abajo (B arriba, A abajo): " << (wfc.is3DCompatible(up, c, 1, 0) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Norte (B sur, A norte):    " << (wfc.is3DCompatible(c, north, 1, 0) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Sur (B norte, A sur):      " << (wfc.is3DCompatible(c, south, 1, 0) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Este (B oeste, A este):    " << (wfc.is3DCompatible(c, east, 1, 0) ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Oeste (B este, A oeste):   " << (wfc.is3DCompatible(c, west, 1, 0) ? "Compatible" : "No compatible") << std::endl;
}

void testNoCompatibility()
{
    // Cada patrón no permite ningún otro (ni a sí mismo) en ninguna dirección
    Object3D patternA(0, 1.0, Constraint3D({}, {}, {}, {}, {}, {}));
    Object3D patternB(1, 1.0, Constraint3D({}, {}, {}, {}, {}, {}));

    Wfc3D wfc({patternA, patternB}, {1.0, 1.0}, {2, 2, 2});

    // Pruebas de compatibilidad
    bool ab = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 0, 1);
    bool aa = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 0, 0);
    bool ba = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 1, 0);
    bool bb = wfc.is3DCompatible({0, 0, 0}, {0, 0, 1}, 1, 1);

    std::cout << "Compatibilidad A con B: " << (ab ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Compatibilidad A con A: " << (aa ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Compatibilidad B con A: " << (ba ? "Compatible" : "No compatible") << std::endl;
    std::cout << "Compatibilidad B con B: " << (bb ? "Compatible" : "No compatible") << std::endl;

    // Si ejecutas el WFC, debe fallar por contradicción
    if (!wfc.executeWfc3D())
    {
        std::cout << "Correcto: El WFC falló por contradicción, como se esperaba.\n";
    }
    else
    {
        std::cout << "Error: El WFC no debería haber generado una solución.\n";
    }
}

int main()
{
    display_scene_from_matrix(RoadsExample, roads_colors);
    return 0;
}