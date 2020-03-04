#pragma once
#include "TFilter.h"
#include <vector>

class TBaseMatrixFilter : public TFilter
{
protected:
    int matrixRadius;
    explicit TBaseMatrixFilter(int matrixRadius_ = 1);
    ~TBaseMatrixFilter() = default;
    int getMatrixSize() const { return 2 * matrixRadius + 1; }
    virtual QColor calculatePixelColor(const QImage& image, int x, int y) const = 0;
public:
    QImage applyToImage(const QImage& image);
    classException(InvalidRadiusError, "Radius must be a positive integer.");
};