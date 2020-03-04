#include "TDynamicMatrixFilter.h"

TDynamicMatrixFilter::TDynamicMatrixFilter(int matrixRadius_) : TBaseMatrixFilter(matrixRadius_)
{
}

QColor TDynamicMatrixFilter::calculatePixelColor(const QImage& image, int x, int y) const
{
    std::vector<QColor> colors;
    for (int i = -matrixRadius; i <= matrixRadius; i++)
        for (int j = -matrixRadius; j <= matrixRadius; j++)
        {
            int nearX = clamp(x + j, 0, image.width() - 1);
            int nearY = clamp(y + i, 0, image.height() - 1);
            QColor color = image.pixelColor(nearX, nearY);
            colors.push_back(color);
        }
    QColor color = calculatePropertyColor(colors);
    return color;
}

QColor TDynamicMatrixFilter::calculatePropertyColor(const std::vector<QColor>& colors) const
{
    std::vector<int> red, green, blue;
    for (QColor color : colors)
    {
        red.push_back(color.red());
        green.push_back(color.green());
        blue.push_back(color.blue());
    }
    int redColor = calculateProperty(red);
    int greenColor = calculateProperty(green);
    int blueColor = calculateProperty(blue);
    redColor = clamp(redColor, 0, 255);
    greenColor = clamp(greenColor, 0, 255);
    blueColor = clamp(blueColor, 0, 255);
    return QColor(redColor, greenColor, blueColor);
}
