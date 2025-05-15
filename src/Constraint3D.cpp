#include <Constraint3D.hpp>
#include <stdexcept>

Constraint3D::Constraint3D(const std::vector<unsigned> AllowedIDsAbove,
                           const std::vector<unsigned> AllowedIDsBelow,
                           const std::vector<unsigned> AllowedIDsNorth,
                           const std::vector<unsigned> AllowedIDsEast,
                           const std::vector<unsigned> AllowedIDsSouth,
                           const std::vector<unsigned> AllowedIDsWest)
    : AllowedIDsAbove(AllowedIDsAbove),
      AllowedIDsBelow(AllowedIDsBelow),
      AllowedIDsNorth(AllowedIDsNorth),
      AllowedIDsEast(AllowedIDsEast),
      AllowedIDsSouth(AllowedIDsSouth),
      AllowedIDsWest(AllowedIDsWest)
{
}

Constraint3D::Constraint3D() = default;

std::vector<unsigned> Constraint3D::get_constraints_for_direction(RelativeDirection direction)
{
    switch (direction)
    {
    case ABOVE:
        return this->AllowedIDsAbove;
        break;
    case BELOW:
        return this->AllowedIDsBelow;
        break;
    case NORTH:
        return this->AllowedIDsNorth;
        break;
    case EAST:
        return this->AllowedIDsEast;
        break;
    case SOUTH:
        return this->AllowedIDsSouth;
        break;
    case WEST:
        return this->AllowedIDsWest;
        break;

    default:
        throw std::invalid_argument("Received Invalid Direction");
    }
}

int Constraint3D::get_count_all_constraints() const
{
    return AllowedIDsAbove.size() + AllowedIDsBelow.size() + AllowedIDsNorth.size() +
           AllowedIDsEast.size() + AllowedIDsSouth.size() + AllowedIDsWest.size();
}

std::vector<unsigned> Constraint3D::get_valid_options() const
{
    return validIDs;
}