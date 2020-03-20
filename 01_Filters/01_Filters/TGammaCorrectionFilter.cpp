#include "TGammaCorrectionFilter.h"

QColor TGammaCorrectionFilter::caclulatePixelColor(QColor color, const std::vector<float>& metrics)
{
    int red = static_cast<int>(coefficient * pow(static_cast<float>(color.red()), gamma));
    int green = static_cast<int>(coefficient * pow(static_cast<float>(color.green()), gamma));
    int blue = static_cast<int>(coefficient * pow(static_cast<float>(color.blue()), gamma));
    return QColor(clamp(red, 0, 255), clamp(green, 0, 255), clamp(blue, 0, 255));
}

std::vector<float> TGammaCorrectionFilter::calculateMetrics(const QImage& image)
{
    return std::vector<float>();
}

TGammaCorrectionFilter::TGammaCorrectionFilter(float gamma_, float coefficient_)
{
    gamma = gamma_;
    coefficient = coefficient_;
}
