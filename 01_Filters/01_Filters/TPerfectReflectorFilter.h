#pragma once
#include "TCorrectionFilter.h"

class TPerfectReflectorFilter : public TCorrectionFilter
{
protected:
    enum metric { redMax, greenMax, blueMax };
    virtual QColor caclulatePixelColor(QColor color, const std::vector<float>& metrics);
    virtual std::vector<float> calculateMetrics(const QImage& image);
public:
    TPerfectReflectorFilter() = default;
    ~TPerfectReflectorFilter() = default;
};