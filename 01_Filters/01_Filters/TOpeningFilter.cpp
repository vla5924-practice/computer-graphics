#include "TOpeningFilter.h"

TOpeningFilter::TOpeningFilter(int radius) : TMorphologyFilter(radius)
{
    dilation = TDilationFilter(radius);
    erosion = TErosionFilter(radius);
}

TOpeningFilter::TOpeningFilter(const std::vector<bool>& mask) : TMorphologyFilter(mask)
{
    dilation = TDilationFilter(mask);
    erosion = TErosionFilter(mask);
}

QImage TOpeningFilter::applyToImage(const QImage& image)
{
    QImage filteredImage = erosion.applyToImage(image);;
    filteredImage = dilation.applyToImage(filteredImage);
    return filteredImage;
}