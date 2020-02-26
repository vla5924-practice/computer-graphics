#include "TShiftFilter.h"

QPoint TShiftFilter::caclulatePixelCoordinates(QPoint pixelCoordinates)
{
    int x = pixelCoordinates.x() + dx;
    int y = pixelCoordinates.y() + dy;
    return QPoint(x, y);
}

TShiftFilter::TShiftFilter(int dx_, int dy_)
{
    dx = dx_;
    dy = dy_;
}
