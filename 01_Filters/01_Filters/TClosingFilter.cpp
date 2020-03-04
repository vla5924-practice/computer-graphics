#include "TClosingFilter.h"

TClosingFilter::TClosingFilter(int radius) : TDilationFilter(radius), TErosionFilter(radius)
{
}

TClosingFilter::TClosingFilter(std::vector<bool> mask) : TDilationFilter(mask), TErosionFilter(mask)
{
}

QImage TClosingFilter::applyToImage(const QImage& image)
{
    QImage filteredImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TDilationFilter::calculatePixelColor(image, x, y);
            filteredImage.setPixelColor(x, y, color);
        }
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TErosionFilter::calculatePixelColor(image, x, y);
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}