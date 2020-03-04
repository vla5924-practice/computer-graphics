#pragma once
#include "TBaseMatrixFilter.h"

class TMatrixFilter : public TBaseMatrixFilter
{
protected:
    std::vector<float> matrix;
    explicit TMatrixFilter(int matrixRadius_ = 1);
    ~TMatrixFilter() = default;
    virtual QColor calculatePixelColor(const QImage& image, int x, int y) const;
};