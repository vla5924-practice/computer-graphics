#include "TTopHatFilter.h"

TTopHatFilter::TTopHatFilter(int radius) : TOpeningFilter(radius)
{
}

TTopHatFilter::TTopHatFilter(std::vector<bool> mask) : TOpeningFilter(mask)
{
}

QImage TTopHatFilter::applyToImage(const QImage& image)
{
    QImage filteredImage = TOpeningFilter::applyToImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TFilter::colorSubtraction(image.pixelColor(x, y), filteredImage.pixelColor(x, y));
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}