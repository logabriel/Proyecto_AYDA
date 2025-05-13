#pragma once
#include <vector>

class Constraint3D
{
public:
    Constraint3D();
    Constraint3D(std::vector<unsigned> AllowedIDsAbove,
                 std::vector<unsigned> AllowedIDsBelow,
                 std::vector<unsigned> AllowedIDsNorth,
                 std::vector<unsigned> AllowedIDsEast,
                 std::vector<unsigned> AllowedIDsSouth,
                 std::vector<unsigned> AllowedIDsWest);
    Constraint3D(Constraint3D &&) = default;
    Constraint3D(const Constraint3D &) = default;
    Constraint3D &operator=(Constraint3D &&) = default;
    Constraint3D &operator=(const Constraint3D &) = default;
    ~Constraint3D();

    std::vector<unsigned> get_constraints_for_direction(RelativeDirection direction);

private:
    std::vector<unsigned> AllowedIDsAbove;
    std::vector<unsigned> AllowedIDsBelow;
    std::vector<unsigned> AllowedIDsNorth;
    std::vector<unsigned> AllowedIDsEast;
    std::vector<unsigned> AllowedIDsSouth;
    std::vector<unsigned> AllowedIDsWest;
};

enum RelativeDirection
{
    ABOVE,
    BELOW,
    NORTH,
    EAST,
    SOUTH,
    WEST
};