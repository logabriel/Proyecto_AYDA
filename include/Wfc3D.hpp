#pragma once
#include <vector>
#include <random>
#include <Object3D.hpp>
#include <Scene3D.hpp>

class Wfc3D
{
private:
    std::vector<Object3D> patterns;
    std::vector<double> weights;
    int size_x, size_y, size_z;
    std::vector<std::vector<std::vector<std::set<unsigned>>>> matrix3D;
    std::mt19937 rng;

public:
    Wfc3D(const std::vector<Object3D>& _patterns, const std::vector<double> &_weights, std::tuple<int, int, int> size);
    ~Wfc3D();

    void initializeMatrix3D() noexcept;
    std::tuple<int, int, int> findMinEntropyCell();
    int collapseCell(std::tuple<int, int, int> cell);
    bool is3DCompatible(std::tuple<int, int, int> cell1, std::tuple<int, int, int> cell2, int pattern1, int pattern2);
    void propagate(std::tuple<int, int, int> cell);
    bool executeWfc3D();
    void printMatrix3D() const;
    void toGraphic() const;
};
