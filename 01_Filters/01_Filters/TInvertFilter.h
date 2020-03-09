#pragma once
#include "TPointFilter.h"

class TInvertFilter : public TPointFilter
{
protected:
    QColor caclulatePixelColor(QColor color);

};