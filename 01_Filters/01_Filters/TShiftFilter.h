#pragma once
#include "TDirectPointFilter.h"

class TShiftFilter : public TDirectPointFilter
{
protected:
    QPoint caclulatePixelCoordinates(QPoint pixelCoordinates);
public:
    int dx, dy;
    explicit TShiftFilter(int dx_ = 0, int dy_ = 0);
    ~TShiftFilter() = default;
};