#include "TDilationFilter.h"

int TDilationFilter::calculateProperty(std::vector<int>& values) const
{
    int max = values[0];
    for (int value : values)
        if (value > max)
            max = value;
    return max;
}

TDilationFilter::TDilationFilter(int radius) : TMorphMatrixFilter(radius)
{
}

TDilationFilter::TDilationFilter(std::vector<bool> mask) : TMorphMatrixFilter(mask)
{
}
