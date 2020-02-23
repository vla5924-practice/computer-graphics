#pragma once
#include <QImage>

class TFilter
{
    template <typename Ty> Ty clamp(Ty value, int min, int max);
public:
    TFilter() = default;
    ~TFilter() = default;

    virtual QImage applyToImage(const QImage& image, int radius) = 0;
};

template<typename Ty>
inline Ty TFilter::clamp(Ty value, int min, int max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}
