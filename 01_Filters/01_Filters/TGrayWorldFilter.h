#pragma once
#include "TCorrectionFilter.h"

class TGrayWorldFilter : public TCorrectionFilter
{
protected:
    enum metric { redAvg, greenAvg, blueAvg, avg };
    virtual QColor caclulatePixelColor(QColor color, const std::vector<float>& metrics);
    virtual std::vector<float> calculateMetrics(const QImage& image);
};