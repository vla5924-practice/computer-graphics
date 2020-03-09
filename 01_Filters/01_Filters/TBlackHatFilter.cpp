#include "TBlackHatFilter.h"

TBlackHatFilter::TBlackHatFilter(int radius) : TMorphMatrixFilter(radius)
{
    closing = TClosingFilter(radius);
}

TBlackHatFilter::TBlackHatFilter(const std::vector<bool>& mask) : TMorphMatrixFilter(mask)
{
    closing = TClosingFilter(mask);
}

QImage TBlackHatFilter::applyToImage(const QImage& image)
{
    QImage filteredImage = closing.applyToImage(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = colorSubtraction(filteredImage.pixelColor(x, y), image.pixelColor(x, y));
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}