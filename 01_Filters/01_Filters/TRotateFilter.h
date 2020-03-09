#pragma once
#include "TDirectPointFilter.h"

class TRotateFilter : public TDirectPointFilter
{
protected:
    inline double getRadians(int angle) const;
    QPoint caclulatePixelCoordinates(QPoint pixel);
public:
    int xCenter, yCenter;
    int angle;
    explicit TRotateFilter(int xCenter_ = 0, int yCenter_ = 0, int angle_ = 0);
};