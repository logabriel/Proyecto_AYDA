#pragma once
#include <vector>
#include "Objects3D.hpp"

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
};

Scene3D::Scene3D(int size_x,
                 int size_y,
                 int size_z)
{
    this->size_x = size_x;
    // Object3DSpace scene{};
    // obj3d_matrix
    for (int x = 0; x < size_x; x++)
    {
        Object3DPlane layer{};
        for (int y = 0; y < size_y; y++)
        {
            Object3DVector line3D{};
            for (int z = 0; z < size_z; z++)
            {
                auto pos = Point3Dint{x, y, z};
                line3D.emplace_back(Object3D(pos));
            }
            layer.emplace_back(line3D);
        }
        this->obj3d_matrix.emplace_back(layer);
    }
}

Scene3D::Scene3D(int cubesize)
{
    for (int x = 0; x < cubesize; x++)
    {
        Object3DPlane layer{};
        for (int y = 0; y < cubesize; y++)
        {
            Object3DVector line3D{};
            for (int z = 0; z < cubesize; z++)
            {
                auto pos = Point3Dint{x, y, z};
                line3D.emplace_back(Object3D(pos));
            }
            layer.emplace_back(line3D);
        }
        this->obj3d_matrix.emplace_back(layer);
    }
}

Scene3D::~Scene3D()
{
}
