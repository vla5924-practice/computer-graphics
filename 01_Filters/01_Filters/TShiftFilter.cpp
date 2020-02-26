#include "TShiftFilter.h"

QPoint TShiftFilter::caclulatePixelCoordinates(QPoint pixel)
{
    int x = pixel.x() + dx;
    int y = pixel.y() + dy;
    return QPoint(x, y);
}

TShiftFilter::TShiftFilter(int dx_, int dy_)
{
    dx = dx_;
    dy = dy_;
}
