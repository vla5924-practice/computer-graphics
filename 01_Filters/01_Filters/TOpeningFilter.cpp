#include "TOpeningFilter.h"

TOpeningFilter::TOpeningFilter(int radius) : TErosionFilter(radius), TDilationFilter(radius)
{
}

TOpeningFilter::TOpeningFilter(std::vector<bool> mask) : TErosionFilter(mask), TDilationFilter(mask)
{

}

QImage TOpeningFilter::applyToImage(const QImage& image)
{
    QImage filteredImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TErosionFilter::calculatePixelColor(image, x, y);
            filteredImage.setPixelColor(x, y, color);
        }
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TDilationFilter::calculatePixelColor(image, x, y);
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}