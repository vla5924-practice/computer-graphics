#pragma once
#include "TMorphMatrixFilter.h"
#include "TClosingFilter.h"

class TBlackHatFilter : public TMorphMatrixFilter
{
protected:
    TClosingFilter closing;
public:
    explicit TBlackHatFilter(int radius = 1);
    TBlackHatFilter(const std::vector<bool>& mask);
    QImage applyToImage(const QImage& image);
};