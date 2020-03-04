#pragma once
#include "TBaseMatrixFilter.h"
#include <vector>

class TDynamicMatrixFilter : public TBaseMatrixFilter
{
protected:
    explicit TDynamicMatrixFilter(int matrixRadius_ = 1);
    ~TDynamicMatrixFilter() = default;
    virtual QColor calculatePixelColor(const QImage& image, int x, int y) const;
    virtual QColor calculatePropertyColor(const std::vector<QColor>& colors) const;
    virtual int calculateProperty(std::vector<int>& values) const = 0;
};