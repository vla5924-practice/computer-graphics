#pragma once
#include "TDynamicMatrixFilter.h"

class TMorphMatrixFilter : public TDynamicMatrixFilter
{
protected:
    std::vector<bool> maskMatrix;
    explicit TMorphMatrixFilter(int matrixRadius_ = 1);
    TMorphMatrixFilter(std::vector<bool> maskMatrix_);
    ~TMorphMatrixFilter() = default;
    virtual QColor calculatePixelColor(const QImage & image, int x, int y) const;
    virtual int calculateProperty(std::vector<int> & values) const = 0;
public:
    classException(InvalidMaskMatrixSize, "Error...");
};