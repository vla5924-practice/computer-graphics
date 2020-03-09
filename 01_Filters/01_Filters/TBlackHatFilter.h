#pragma once
#include "TMorphologyFilter.h"
#include "TClosingFilter.h"

class TBlackHatFilter : public TMorphologyFilter
{
protected:
    TClosingFilter closing;
public:
    explicit TBlackHatFilter(int radius = 1);
    TBlackHatFilter(const std::vector<bool>& mask);
    QImage applyToImage(const QImage& image);
};