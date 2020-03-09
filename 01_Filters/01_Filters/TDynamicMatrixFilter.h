#pragma once
#include "TBaseMatrixFilter.h"
#include <vector>

class TDynamicMatrixFilter : public TBaseMatrixFilter
{
protected:
    explicit TDynamicMatrixFilter(int matrixRadius_ = 1);
    virtual QColor calculatePixelColor(const QImage& image, int x, int y) const;
    virtual QColor calculatePropertyColor(const QColor* colors, int colorsCount) const;
    virtual int calculateProperty(int* values, int valuesCount) const;
};