#pragma once
#include "TDynamicMatrixFilter.h"

class TMaximumFilter : public TDynamicMatrixFilter
{
protected:
    int calculateProperty(int* values, int valuesCount) const;
public:
    explicit TMaximumFilter(int radius = 1);
};