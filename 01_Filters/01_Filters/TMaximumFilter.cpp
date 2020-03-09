#include "TMaximumFilter.h"

int TMaximumFilter::calculateProperty(int* values, int valuesCount) const
{
    int max = values[0];
    for (int i = 1; i < valuesCount; i++)
        if (values[i] > max)
            max = values[i];
    return max;
}

TMaximumFilter::TMaximumFilter(int radius) : TDynamicMatrixFilter(radius)
{
}
