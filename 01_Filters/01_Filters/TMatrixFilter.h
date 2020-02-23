#pragma once
#include "TFilter.h"
#include <vector>

class TMatrixFilter : public TFilter
{
protected:
    std::vector<float> matrix;
    int matrixRadius;
    inline int getMatrixSize() const;
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    //TMatrixFilter() = default;
    explicit TMatrixFilter(int matrixRadius_ = 1);
    ~TMatrixFilter() = default;
    QImage applyToImage(const QImage& image);

};