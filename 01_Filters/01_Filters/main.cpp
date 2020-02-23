#include "includes.h"

int main(int argc, char *argv[])
{
    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-p") and (i + 1 < argc))
            fileName = argv[i + 1];

    QImage image, filteredImage;
    image.load(fileName.c_str());
    image.save("test_copy.png");

    TInvertFilter invFilter;
    filteredImage = invFilter.applyToImage(image);
    filteredImage.save("test_inv.png");

    TGrayScaleFilter grayFilter;
    filteredImage = grayFilter.applyToImage(image);
    filteredImage.save("test_gray.png");

    TBlurFilter blurFilter(2);
    filteredImage = blurFilter.applyToImage(image);
    filteredImage.save("test_blur.png");

    TGaussianBlurFilter gBlurFilter;
    filteredImage = gBlurFilter.applyToImage(image);
    filteredImage.save("test_gblur.png");

    return 0;
}
