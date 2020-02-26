#include "TMedianFilter.h"

int TMedianFilter::calculateMedian(std::vector<int>& values) const
{
    std::sort(values.begin(), values.end());
    return values[values.size() / 2U];
}

QColor TMedianFilter::calculateMedianColor(const std::vector<QColor>& colors) const
{
    std::vector<int> red, green, blue;
    for (QColor color : colors)
    {
        red.push_back(color.red());
        green.push_back(color.green());
        blue.push_back(color.blue());
    }
    int redMedian   = calculateMedian(red);
    int greenMedian = calculateMedian(green);
    int blueMedian  = calculateMedian(blue);
    redMedian   = clamp(redMedian, 0, 255);
    greenMedian = clamp(greenMedian, 0, 255);
    blueMedian  = clamp(blueMedian, 0, 255);
    return QColor(redMedian, greenMedian, blueMedian);
}

QColor TMedianFilter::calculatePixelColor(const QImage& image, int x, int y) const
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
    QColor medianColor = calculateMedianColor(colors);
    return medianColor;
}

TMedianFilter::TMedianFilter(int radius) : TMatrixFilter()
{
    if (radius < 1)
        throw InvalidRadiusError();
    matrix.resize(1);
    matrixRadius = radius;
}
