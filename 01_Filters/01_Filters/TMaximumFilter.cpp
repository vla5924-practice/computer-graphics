#include "TMaximumFilter.h"

int TMaximumFilter::calculateMaximum(std::vector<int>& values) const
{
    int max = values[0];
    for (int value : values)
        if (value > max)
            max = value;
    return max;
}

QColor TMaximumFilter::calculateMaximumColor(const std::vector<QColor>& colors) const
{
    std::vector<int> red, green, blue;
    for (QColor color : colors)
    {
        red.push_back(color.red());
        green.push_back(color.green());
        blue.push_back(color.blue());
    }
    int redMax = calculateMaximum(red);
    int greenMax = calculateMaximum(green);
    int blueMax = calculateMaximum(blue);
    redMax = clamp(redMax, 0, 255);
    greenMax = clamp(greenMax, 0, 255);
    blueMax = clamp(blueMax, 0, 255);
    return QColor(redMax, greenMax, blueMax);
}

QColor TMaximumFilter::calculatePixelColor(const QImage& image, int x, int y) const
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
    QColor maximumColor = calculateMaximumColor(colors);
    return maximumColor;
}

TMaximumFilter::TMaximumFilter(int radius) : TMatrixFilter()
{
    if (radius < 1)
        throw InvalidRadiusError();
    matrix.resize(1);
    matrixRadius = radius;
}
