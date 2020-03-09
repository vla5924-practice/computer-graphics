#pragma once
#include "TFilter.h"

class TPointFilter : public TFilter
{
protected:
    virtual QColor caclulatePixelColor(QColor color) = 0;
public:
    QImage applyToImage(const QImage& image);
};