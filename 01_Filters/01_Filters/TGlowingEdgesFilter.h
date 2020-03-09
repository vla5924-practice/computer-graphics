#pragma once
#include "TComplexFilter.h"
#include "TMedianFilter.h"
#include "TSobelYFilter.h"
#include "TMaximumFilter.h"

class TGlowingEdgesFilter : public TComplexFilter
{
public:
    QImage applyToImage(const QImage& image);
};