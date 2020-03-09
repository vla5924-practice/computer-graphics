#include "TOpeningFilter.h"

TOpeningFilter::TOpeningFilter(int radius) : TMorphMatrixFilter(radius)
{
    dilation = TDilationFilter(radius);
    erosion = TErosionFilter(radius);
}

TOpeningFilter::TOpeningFilter(const std::vector<bool>& mask) : TMorphMatrixFilter(mask)
{
    dilation = TDilationFilter(mask);
    erosion = TErosionFilter(mask);
}

QImage TOpeningFilter::applyToImage(const QImage& image)
{
    QImage filteredImage;
    filteredImage = erosion.applyToImage(filteredImage);
    filteredImage = dilation.applyToImage(filteredImage);
    return filteredImage;
}