#pragma once
#include "TMorphologyFilter.h"
#include "TDilationFilter.h"
#include "TErosionFilter.h"

class TOpeningFilter : public TMorphologyFilter
{
protected:
    TErosionFilter erosion;
    TDilationFilter dilation;
public:
    explicit TOpeningFilter(int radius = 1);
    TOpeningFilter(const std::vector<bool>& mask);
    QImage applyToImage(const QImage& image);
};