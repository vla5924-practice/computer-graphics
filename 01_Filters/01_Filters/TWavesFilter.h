#pragma once
#include "TDirectPointFilter.h"

class TWavesFilter : public TDirectPointFilter
{
protected:
    QPoint caclulatePixelCoordinates(QPoint pixel);
};