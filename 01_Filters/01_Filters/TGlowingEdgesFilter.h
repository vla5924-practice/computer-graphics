#pragma once
#include "TComplexFilter.h"
#include "TMedianFilter.h"
#include "TSobelYFilter.h"
#include "TMaximumFilter.h"

class TGlowingEdgesFilter : public TComplexFilter
{
public:
    TGlowingEdgesFilter() = default;
    ~TGlowingEdgesFilter() = default;
    QImage applyToImage(const QImage& image);
};