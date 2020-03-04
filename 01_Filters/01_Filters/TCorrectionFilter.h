#pragma once
#include "TFilter.h"
#include <vector>

class TCorrectionFilter : public TFilter
{
protected:
    TCorrectionFilter() = default;
    ~TCorrectionFilter() = default;
    virtual QColor caclulatePixelColor(QColor color, const std::vector<float>& metrics) = 0;
    virtual std::vector<float> calculateMetrics(const QImage& image);
public:
    QImage applyToImage(const QImage& image);
};