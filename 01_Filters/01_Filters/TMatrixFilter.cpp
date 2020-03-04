#include "TMatrixFilter.h"

QColor TMatrixFilter::calculatePixelColor(const QImage& image, int x, int y) const
{
    int red = 0, green = 0, blue = 0;
    int matrixSize = getMatrixSize();
    for(int i = -matrixRadius; i <= matrixRadius; i++)
        for (int j = -matrixRadius; j <= matrixRadius; j++)
        {
            int index = (i + matrixRadius) * matrixSize + j + matrixRadius;
            int nearX = clamp(x + j, 0, image.width() - 1);
            int nearY = clamp(y + i, 0, image.height() - 1);
            QColor color = image.pixelColor(nearX, nearY);
            red   += color.red()   * matrix[index];
            green += color.green() * matrix[index];
            blue  += color.blue()  * matrix[index];
        }
    red = clamp(red, 0, 255);
    green = clamp(green, 0, 255);
    blue = clamp(blue, 0, 255);
    return QColor(red, green, blue);
}

TMatrixFilter::TMatrixFilter(int matrixRadius_) : TBaseMatrixFilter(matrixRadius_)
{
    int matrixSize = getMatrixSize();
    matrix.resize(static_cast<size_t>(matrixSize * matrixSize));
}