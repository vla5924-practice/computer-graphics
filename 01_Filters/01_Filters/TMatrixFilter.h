#pragma once
#include "TBaseMatrixFilter.h"

class TMatrixFilter : public TBaseMatrixFilter
{
protected:
    float* matrix;
    explicit TMatrixFilter(int matrixRadius_ = 1);
    ~TMatrixFilter();
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
};