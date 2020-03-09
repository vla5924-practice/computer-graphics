#include "TErosionFilter.h"

int TErosionFilter::calculateProperty(int* values, int valuesCount) const
{
    int min = values[0];
    for (int i = 1; i < valuesCount; i++)
        if (values[i] < min)
            min = values[i];
    return min;
}

TErosionFilter::TErosionFilter(int radius) : TMorphologyFilter(radius)
{
}

TErosionFilter::TErosionFilter(const std::vector<bool>& mask) : TMorphologyFilter(mask)
{
}