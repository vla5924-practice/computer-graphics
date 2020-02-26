#include "TGlowingEdgesFilter.h"

QImage TGlowingEdgesFilter::applyToImage(const QImage& image)
{
    QImage filteredImage;
    TMedianFilter medianFilter;
    TSobelYFilter sobelFilter;
    TMaximumFilter maximumFilter;
    filteredImage = medianFilter.applyToImage(image);
    filteredImage = sobelFilter.applyToImage(filteredImage);
    filteredImage = maximumFilter.applyToImage(filteredImage);
    return filteredImage;
}
