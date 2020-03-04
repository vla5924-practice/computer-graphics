#include "TFilter.h"

bool TFilter::validCoordinate(QPoint point, int width, int height) const
{
    bool xValid = (point.x() >= 0) && (point.x() <= width - 1);
    bool yValid = (point.y() >= 0) && (point.y() <= height - 1);
    return xValid && yValid;
}
