#pragma once
#include "TMatrixFilter.h"

class TMaximumFilter : public TMatrixFilter
{
protected:
    int calculateMaximum(std::vector<int>& values) const;
    QColor calculateMaximumColor(const std::vector<QColor>& colors) const;
    QColor calculatePixelColor(const QImage& image, int x, int y) const;
public:
    explicit TMaximumFilter(int radius = 1);
    ~TMaximumFilter() = default;
};