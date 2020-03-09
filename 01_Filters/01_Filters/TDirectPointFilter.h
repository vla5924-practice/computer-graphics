#pragma once
#include "TFilter.h"

class TDirectPointFilter : public TFilter
{
protected:
    virtual QPoint caclulatePixelCoordinates(QPoint pixel) = 0;
public:
    QImage applyToImage(const QImage& image);
};