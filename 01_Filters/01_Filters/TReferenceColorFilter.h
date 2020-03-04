#pragma once
#include "TCorrectionFilter.h"

class TReferenceColorFilter : public TCorrectionFilter
{
protected:
    enum metric { redCoef, greenCoef, blueCoef };
    virtual QColor caclulatePixelColor(QColor color, const std::vector<float>& metrics);
    virtual std::vector<float> calculateMetrics(QColor sourceColor, QColor controlColor);
public:
    TReferenceColorFilter() = default;
    ~TReferenceColorFilter() = default;
    QImage applyToImage(const QImage& image, QPoint sourcePixel, QColor controlColor);
};