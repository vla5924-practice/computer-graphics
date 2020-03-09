#pragma once
#include "TMorphologyFilter.h"

class TDilationFilter : public TMorphologyFilter
{
    friend class TOpeningFilter;
protected:
    int calculateProperty(int* values, int valuesCount) const;
public:
    explicit TDilationFilter(int radius = 1);
    TDilationFilter(const std::vector<bool>& mask);
};