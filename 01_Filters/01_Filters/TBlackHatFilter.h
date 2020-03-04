#pragma once
#include "TClosingFilter.h"

class TBlackHatFilter : public TClosingFilter
{
public:
    explicit TBlackHatFilter(int radius = 1);
    TBlackHatFilter(std::vector<bool> mask);
    ~TBlackHatFilter() = default;
    QImage applyToImage(const QImage& image);
};