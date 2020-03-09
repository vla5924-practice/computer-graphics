#pragma once
#include "TCorrectionFilter.h"

class TLinearCorrectionFilter : public TCorrectionFilter
{
protected:
    enum metric { redMin, greenMin, blueMin, redMax, greenMax, blueMax };
    virtual QColor caclulatePixelColor(QColor color, const std::vector<float> & metrics);
    virtual std::vector<float> calculateMetrics(const QImage & image);
};