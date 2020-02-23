#pragma once
#include "TPointFilter.h"

class TSepiaFilter : public TPointFilter
{
protected:
    QColor caclulatePixelColor(QColor color);
public:
    TSepiaFilter() = default;
    ~TSepiaFilter() = default;
};