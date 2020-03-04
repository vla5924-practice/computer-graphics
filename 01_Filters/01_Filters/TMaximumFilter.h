#pragma once
#include "TDynamicMatrixFilter.h"

class TMaximumFilter : public TDynamicMatrixFilter
{
protected:
    int calculateProperty(std::vector<int>& values) const;
public:
    explicit TMaximumFilter(int radius = 1);
    ~TMaximumFilter() = default;
};