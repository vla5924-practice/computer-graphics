#pragma once
#include "TDynamicMatrixFilter.h"

class TMedianFilter : public TDynamicMatrixFilter
{
protected:
    int calculateProperty(std::vector<int>& values) const;
public:
    explicit TMedianFilter(int radius = 1);
    ~TMedianFilter() = default;
};