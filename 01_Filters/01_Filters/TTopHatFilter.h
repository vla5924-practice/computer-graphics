#pragma once
#include "TMorphologyFilter.h"
#include "TOpeningFilter.h"

class TTopHatFilter : public TMorphologyFilter
{
protected:
    TOpeningFilter opening;
public:
    explicit TTopHatFilter(int radius = 1);
    TTopHatFilter(const std::vector<bool>& mask);
    QImage applyToImage(const QImage & image);
};