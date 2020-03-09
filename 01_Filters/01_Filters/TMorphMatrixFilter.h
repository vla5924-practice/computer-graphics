#pragma once
#include "TDynamicMatrixFilter.h"

class TMorphMatrixFilter : public TDynamicMatrixFilter
{
protected:
    std::vector<bool> maskMatrix;
    int maskPower;
    explicit TMorphMatrixFilter(int matrixRadius_ = 1);
    TMorphMatrixFilter(const std::vector<bool>& maskMatrix_);
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    classException(InvalidMaskMatrixSize, "Error...");
};