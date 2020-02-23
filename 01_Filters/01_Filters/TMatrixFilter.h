#pragma once
#include "TFilter.h"
#include <vector>

class TMatrixFilter : public TFilter
{
protected:
    std::vector<float> matrix;
    int matrixRadius;
    explicit TMatrixFilter(int matrixRadius_ = 1);
    ~TMatrixFilter() = default;
    inline int getMatrixSize() const;
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    QImage applyToImage(const QImage& image);
    classException(InvalidRadiusError, "Radius must be a positive integer.");
};