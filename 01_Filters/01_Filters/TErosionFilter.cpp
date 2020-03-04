#include "TErosionFilter.h"

int TErosionFilter::calculateProperty(std::vector<int>& values) const
{
    int min = values[0];
    for (int value : values)
        if (value < min)
            min = value;
    return min;
}

TErosionFilter::TErosionFilter(int radius) : TMorphMatrixFilter(radius)
{
}

TErosionFilter::TErosionFilter(std::vector<bool> mask) : TMorphMatrixFilter(mask)
{
}