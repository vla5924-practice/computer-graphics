#include "TDilationFilter.h"

int TDilationFilter::calculateProperty(int* values, int valuesCount) const
{
    int max = values[0];
    for (int i = 1; i < valuesCount; i++)
        if (values[i] > max)
            max = values[i];
    return max;
}

TDilationFilter::TDilationFilter(int radius) : TMorphologyFilter(radius)
{
}

TDilationFilter::TDilationFilter(const std::vector<bool>& mask) : TMorphologyFilter(mask)
{
}
