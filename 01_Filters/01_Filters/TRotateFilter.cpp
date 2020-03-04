#include "TRotateFilter.h"

inline double TRotateFilter::getRadians(int angle) const
{
    return 3.141592 * angle / 180.;
}

QPoint TRotateFilter::caclulatePixelCoordinates(QPoint pixel)
{
    int x = (pixel.x() - xCenter) * cos(getRadians(angle)) - (pixel.y() - yCenter) * sin(getRadians(angle)) + xCenter;
    int y = (pixel.x() - xCenter) * sin(getRadians(angle)) + (pixel.y() - yCenter) * cos(getRadians(angle)) + yCenter;
    return QPoint(x, y);
}

TRotateFilter::TRotateFilter(int xCenter_, int yCenter_, int angle_)
{
    xCenter = xCenter_;
    yCenter = yCenter_;
    angle = angle_;
}
