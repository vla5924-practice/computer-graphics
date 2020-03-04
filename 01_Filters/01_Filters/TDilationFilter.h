#pragma once
#include "TMorphMatrixFilter.h"

class TDilationFilter : public TMorphMatrixFilter
{
    friend class TOpeningFilter;
protected:
    int calculateProperty(std::vector<int>& values) const;
public:
    explicit TDilationFilter(int radius = 1);
    TDilationFilter(std::vector<bool> mask);
    ~TDilationFilter() = default;
};