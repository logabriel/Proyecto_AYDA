#pragma once
#include <vector>
#include "Object3D.hpp"

using Object3DVector = std::vector<Object3D>;
using Object3DPlane = std::vector<Object3DVector>;
using Object3DSpace = std::vector<Object3DPlane>;

class Scene3D
{
private:
    Object3DSpace obj3d_matrix;
    int size_x;
    int size_y;
    int size_z;

public:
    Scene3D(int size_x,
            int size_y,
            int size_z);
    Scene3D(int cubesize);
    ~Scene3D();
    // void initialize() noexcept;
    void printMatrix() const;
};
