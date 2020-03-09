#include "TMedianFilter.h"

int TMedianFilter::calculateProperty(int* values, int valuesCount) const
{
    std::sort(values, values + valuesCount);
    return values[valuesCount / 2U];
}


TMedianFilter::TMedianFilter(int radius) : TDynamicMatrixFilter(radius)
{
}
