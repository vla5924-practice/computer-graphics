#include "TCorrectionFilter.h"

std::vector<float> TCorrectionFilter::calculateMetrics(const QImage& image)
{
    return std::vector<float>();
}

QImage TCorrectionFilter::applyToImage(const QImage& image)
{
    QImage filteredImage(image);
    std::vector<float> metrics = calculateMetrics(image);
    for (int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = image.pixelColor(x, y);
            color = caclulatePixelColor(color, metrics);
            filteredImage.setPixelColor(x, y, color);
        }
    return filteredImage;
}
