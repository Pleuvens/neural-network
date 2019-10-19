#include <cmath>
#include "constants.hh"

bool isEqual(const float lhs, const float rhs)
{
    return std::abs(lhs - rhs) < EPSILON;
}

bool isNotEqual(const float lhs, const float rhs)
{
    return std::abs(lhs - rhs) > EPSILON;
}
