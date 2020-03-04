#pragma once
#include <QImage>
#include "Exception.h"

class TFilter
{
protected:
    TFilter() = default;
    ~TFilter() = default;
    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
    bool validCoordinate(QPoint point, int width, int height) const;
    //forEachPixel(const QImage& image, QImage& resultImage, void(*procedure)(QImage& image, int x, int y)) const;
public:
    virtual QImage applyToImage(const QImage& image) = 0;
};

template<typename Ty>
inline Ty TFilter::clamp(Ty value, int min, int max) const
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}