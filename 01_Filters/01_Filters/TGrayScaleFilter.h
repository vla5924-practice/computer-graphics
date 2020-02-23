#pragma once
#include "TPointFilter.h"

class TGrayScaleFilter : public TPointFilter
{
protected:
    QColor caclulatePixelColor(QColor color);
public:
    TGrayScaleFilter() = default;
    ~TGrayScaleFilter() = default;
};