#include "TMedianFilter.h"

int TMedianFilter::calculateProperty(std::vector<int>& values) const
{
    std::sort(values.begin(), values.end());
    return values[values.size() / 2U];
}


TMedianFilter::TMedianFilter(int radius) : TDynamicMatrixFilter(radius)
{
}
