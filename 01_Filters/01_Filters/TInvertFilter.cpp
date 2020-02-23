#include "TInvertFilter.h"

QImage TInvertFilter::applyToImage(const QImage& image, int radius)
{
    QImage invImage(image);
    for(int x = 0; x < image.width(); x++)
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = image.pixelColor(x, y);
            color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
            invImage.setPixelColor(x, y, color);
        }
    return invImage;
}
