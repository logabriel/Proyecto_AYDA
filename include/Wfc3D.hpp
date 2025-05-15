#pragma once
#include <vector>
#include <random>
#include <Object3D.hpp>
#include <Scene3D.hpp>
#include <optional>
class Wfc3D
{
private:
    std::vector<Object3D> patterns;
    std::vector<double> weights;
    int size_x, size_y, size_z;
    std::vector<std::vector<std::vector<std::set<unsigned int>>>> matrix3D;
    std::mt19937 rng;

public:
    Wfc3D(const std::vector<Object3D> &_patterns, const std::vector<double> &_weights, std::tuple<int, int, int> size, std::optional<unsigned> custom_seed = std::nullopt);
    ~Wfc3D();

    void initializeMatrix3D() noexcept; // esto deberia estar en Scene3D (?)
    Coords3DInt findMinEntropyCell();
    int collapseCell(Coords3DInt cell_position);
    bool is3DCompatible(Coords3DInt cell1, Coords3DInt cell2, 
        int pattern1, int pattern2);
    bool is3DCompatible(Coords3DInt cell_position);
    void propagateConstraints(Coords3DInt cell);
    bool executeWfc3D();
    void printResult() const;
    std::vector<Coords3DInt> getNeighbors(int x, int y, int z) const;
    bool isValidCell(int x, int y, int z) const;

    // void toGraphic() const; // La representacion grafica se deberia hacer en otra clase
};
