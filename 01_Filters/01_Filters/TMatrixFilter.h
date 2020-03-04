#pragma once
#include "TBaseMatrixFilter.h"

class TMatrixFilter : public TBaseMatrixFilter
{
protected:
    std::vector<float> matrix;
    explicit TMatrixFilter(int matrixRadius_ = 1);
    ~TMatrixFilter() = default;
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
};