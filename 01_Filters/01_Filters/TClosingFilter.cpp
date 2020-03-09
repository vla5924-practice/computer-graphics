#include "TClosingFilter.h"

TClosingFilter::TClosingFilter(int radius) : TMorphMatrixFilter(radius)
{
    dilation = TDilationFilter(radius);
    erosion = TErosionFilter(radius);
}

TClosingFilter::TClosingFilter(const std::vector<bool>& mask) : TMorphMatrixFilter(mask)
{
    dilation = TDilationFilter(mask);
    erosion = TErosionFilter(mask);
}

QImage TClosingFilter::applyToImage(const QImage& image)
{
    QImage filteredImage;
    filteredImage = dilation.applyToImage(filteredImage);
    filteredImage = erosion.applyToImage(filteredImage);
    return filteredImage;
}