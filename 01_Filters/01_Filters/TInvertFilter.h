#pragma once
#include "TFilter.h"

class TInvertFilter : public TFilter
{
public:
    TInvertFilter() = default;
    ~TInvertFilter() = default;
    QImage applyToImage(const QImage& image);
};