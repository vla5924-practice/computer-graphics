#include "TMaximumFilter.h"

int TMaximumFilter::calculateProperty(std::vector<int>& values) const
{
    int max = values[0];
    for (int value : values)
        if (value > max)
            max = value;
    return max;
}

TMaximumFilter::TMaximumFilter(int radius) : TDynamicMatrixFilter(radius)
{
}
