#pragma once
#include <vector>

enum RelativeDirection
{
    ABOVE,
    BELOW,
    NORTH,
    EAST,
    SOUTH,
    WEST
};
class Constraint3D
{
public:
    Constraint3D();
    Constraint3D(const std::vector<unsigned> AllowedIDsAbove,
                 const std::vector<unsigned> AllowedIDsBelow,
                 const std::vector<unsigned> AllowedIDsNorth,
                 const std::vector<unsigned> AllowedIDsEast,
                 const std::vector<unsigned> AllowedIDsSouth, 
                 const std::vector<unsigned> AllowedIDsWest);
    Constraint3D(Constraint3D &&) = default;
    Constraint3D(const Constraint3D &) = default;
    Constraint3D &operator=(Constraint3D &&) = default;
    Constraint3D &operator=(const Constraint3D &) = default;
    ~Constraint3D() = default;

    std::vector<unsigned> get_constraints_for_direction(RelativeDirection direction);
    int get_count_all_constraints() const;
    std::vector<unsigned> get_valid_options() const;

private:
    std::vector<unsigned> AllowedIDsAbove;
    std::vector<unsigned> AllowedIDsBelow;
    std::vector<unsigned> AllowedIDsNorth;
    std::vector<unsigned> AllowedIDsEast;
    std::vector<unsigned> AllowedIDsSouth;
    std::vector<unsigned> AllowedIDsWest;

    // To identify the valid IDs given the constraints
    std::vector<unsigned> validIDs;
};
