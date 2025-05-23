
#pragma once
#include <vector>
#include <random>
#include <Object3D.hpp>
#include <Scene3D.hpp>
#include <optional>
#include <stack>
#include <tuple>

struct DecisionPoint {
        Coords3DInt cell;
        std::vector<std::vector<std::vector<std::set<unsigned int>>>> history;
        std::set<unsigned int> triedPatterns;
    };

class Wfc3D
{
private:
    std::vector<Object3D> patterns;
    std::vector<double> weights;
    int size_x, size_y, size_z;
    std::vector<std::vector<std::vector<std::set<unsigned int>>>> matrix3D;
    std::mt19937 rng;

    void initializeMatrix3D() noexcept;
    Coords3DInt findMinEntropyCell();
    std::optional<unsigned> attemptCollapse(Coords3DInt cell_position);
    //bool is3DCompatible(Coords3DInt cell1, Coords3DInt cell2, int pattern1, int pattern2);
    bool is3DCompatible(Coords3DInt cell_position);
    bool propagateConstraints(Coords3DInt cell);
    std::vector<Coords3DInt> getNeighbors(int x, int y, int z) const;
    bool isValidCell(int x, int y, int z) const;

    //backtracking
    std::stack<DecisionPoint> decisionStack;
    void saveState(const Coords3DInt& cell);
    bool backtrack();
    int maxAttempts = 1000;
    int attempts = 0;

public:
    Wfc3D(const std::vector<Object3D> &_patterns, const std::vector<double> &_weights, std::tuple<int, int, int> size, std::optional<unsigned> custom_seed = std::nullopt);
    ~Wfc3D();
    bool executeWfc3D();
    void printResult() const;
    void createBaseLayer(unsigned int patternId);
    std::tuple<int, int, int> getSizes() const { return std::make_tuple(size_x, size_y, size_z); }
    std::vector<std::vector<std::vector<std::set<unsigned int>>>> getMatrix3D() const { return matrix3D; }
    bool is3DCompatible(Coords3DInt cell1, Coords3DInt cell2, int pattern1, int pattern2);
};