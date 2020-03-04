#include "TBlackHatFilter.h"

TBlackHatFilter::TBlackHatFilter(int radius) : TClosingFilter(radius)
{
}

TBlackHatFilter::TBlackHatFilter(std::vector<bool> mask) : TClosingFilter(mask)
{
}

QImage TBlackHatFilter::applyToImage(const QImage& image)
{
    QImage filteredImage = TClosingFilter::applyToImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = TFilter::colorSubtraction(filteredImage.pixelColor(x, y), filteredImage.pixelColor(x, y));
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}