#pragma once
#include "TPointFilter.h"

class TInvertFilter : public TPointFilter
{
public:
    TInvertFilter() = default;
    ~TInvertFilter() = default;
    QImage applyToImage(const QImage& image);
};