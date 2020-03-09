#pragma once
#include "TDynamicMatrixFilter.h"

class TMedianFilter : public TDynamicMatrixFilter
{
protected:
    int calculateProperty(int* values, int valuesCount) const;
public:
    explicit TMedianFilter(int radius = 1);
};