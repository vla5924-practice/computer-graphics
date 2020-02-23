#pragma once
#include "TMatrixFilter.h"

class TMedianFilter : public TMatrixFilter
{
protected:
    int calculateMedian(std::vector<int>& values) const;
    QColor calculateMedianColor(const std::vector<QColor>& colors) const;
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    explicit TMedianFilter(int radius = 1);
    ~TMedianFilter() = default;
};