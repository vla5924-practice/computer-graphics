#pragma once
#include "TMorphologyFilter.h"

class TErosionFilter : public TMorphologyFilter
{
protected:
    int calculateProperty(int* values, int valuesCount) const;
public:
    explicit TErosionFilter(int radius = 1);
    TErosionFilter(const std::vector<bool>& mask);
};