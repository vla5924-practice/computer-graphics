#include "Filters.h"

void inversion(QImage& image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            QColor color = image.pixelColor(x, y);
            color.setRed(255 - color.red());
            color.setGreen(255 - color.green());
            color.setBlue(255 - color.blue());
            image.setPixelColor(x, y, color);
        }
    }
}

void averaging(QImage& image)
{
    std::array<QColor, 9> colors;
    for (int x = 1; x < image.width() - 1; x += 4)
    {
        for (int y = 1; y < image.height() - 1; y += 4)
        {
            colors[0] = image.pixelColor(x - 1, y - 1);
            colors[1] = image.pixelColor(x, y - 1);
            colors[2] = image.pixelColor(x + 1, y - 1);
            colors[3] = image.pixelColor(x - 1, y);
            colors[4] = image.pixelColor(x, y);
            colors[5] = image.pixelColor(x + 1, y);
            colors[6] = image.pixelColor(x - 1, y + 1);
            colors[7] = image.pixelColor(x, y + 1);
            colors[8] = image.pixelColor(x + 1, y + 1);
            int red = 0, green = 0, blue = 0;
            for (QColor color : colors)
            {
                red   += color.red();
                green += color.green();
                blue  += color.blue();
            }
            QColor newColor(red / 9, green / 9, blue / 9);
            image.setPixelColor(x, y, newColor);
        }
    }
}