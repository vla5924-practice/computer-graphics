#pragma once
#include "TPointFilter.h"

class TBrightnessFilter : public TPointFilter
{
protected:
    QColor caclulatePixelColor(QColor color);
public:
    int delta;
    explicit TBrightnessFilter(int delta = 0);
    ~TBrightnessFilter() = default;
};