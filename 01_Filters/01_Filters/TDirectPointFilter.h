#pragma once
#include "TFilter.h"

class TDirectPointFilter : public TFilter
{
protected:
    TDirectPointFilter() = default;
    ~TDirectPointFilter() = default;
    virtual QPoint caclulatePixelCoordinates(QPoint pixelCoordinates) = 0;
public:
    QImage applyToImage(const QImage& image);
};