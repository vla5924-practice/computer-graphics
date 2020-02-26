#pragma once
#include "TFilter.h"

class TComplexFilter : public TFilter
{
protected:
    TComplexFilter() = default;
    ~TComplexFilter() = default;
public:
    QImage applyToImage(const QImage& image) = 0;
};