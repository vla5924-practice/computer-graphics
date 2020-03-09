#pragma once
#include "TMorphMatrixFilter.h"

class TErosionFilter : public TMorphMatrixFilter
{
protected:
    int calculateProperty(int* values, int valuesCount) const;
public:
    explicit TErosionFilter(int radius = 1);
    TErosionFilter(const std::vector<bool>& mask);
};