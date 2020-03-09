#pragma once
#include "TMorphologyFilter.h"
#include "TErosionFilter.h"
#include "TDilationFilter.h"

class TClosingFilter : public TMorphologyFilter
{
protected:
    TDilationFilter dilation;
    TErosionFilter erosion;
public:
    explicit TClosingFilter(int radius = 1);
    TClosingFilter(const std::vector<bool>& mask);
    QImage applyToImage(const QImage& image);
};