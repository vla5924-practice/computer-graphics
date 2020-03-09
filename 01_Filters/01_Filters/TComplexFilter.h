#pragma once
#include "TFilter.h"

class TComplexFilter : public TFilter
{
public:
    QImage applyToImage(const QImage& image) = 0;
};