#pragma once
#include "TDynamicMatrixFilter.h"

class TMorphologyFilter : public TDynamicMatrixFilter
{
protected:
    std::vector<bool> maskMatrix;
    int maskPower;
    explicit TMorphologyFilter(int matrixRadius_ = 1);
    TMorphologyFilter(const std::vector<bool>& maskMatrix_);
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    classException(InvalidMaskMatrixSize, "Error...");
};