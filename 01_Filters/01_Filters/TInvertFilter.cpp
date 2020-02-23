#include "TInvertFilter.h"

QColor TInvertFilter::caclulatePixelColor(QColor color)
{
    QColor newColor(255 - color.red(), 255 - color.green(), 255 - color.blue());
    return newColor;
}
