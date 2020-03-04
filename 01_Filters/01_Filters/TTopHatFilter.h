#pragma once
#include "TOpeningFilter.h"

class TTopHatFilter : public TOpeningFilter
{
public:
    explicit TTopHatFilter(int radius = 1);
    TTopHatFilter(std::vector<bool> mask);
    ~TTopHatFilter() = default;
    QImage applyToImage(const QImage & image);
};