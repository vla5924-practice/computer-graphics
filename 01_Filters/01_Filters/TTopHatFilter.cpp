#include "TTopHatFilter.h"

TTopHatFilter::TTopHatFilter(int radius) : TMorphMatrixFilter(radius)
{
    opening = TOpeningFilter(radius);
}

TTopHatFilter::TTopHatFilter(const std::vector<bool>& mask) : TMorphMatrixFilter(mask)
{
    opening = TOpeningFilter(mask);
}

QImage TTopHatFilter::applyToImage(const QImage& image)
{
    QImage filteredImage = opening.applyToImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = colorSubtraction(image.pixelColor(x, y), filteredImage.pixelColor(x, y));
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}