#pragma once
#include "TMorphMatrixFilter.h"

class TErosionFilter : public TMorphMatrixFilter
{
protected:
    int calculateProperty(std::vector<int>& values) const;
public:
    explicit TErosionFilter(int radius = 1);
    TErosionFilter(std::vector<bool> mask);
    ~TErosionFilter() = default;
};