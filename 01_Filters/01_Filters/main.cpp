#include "includes.h"

int main(int argc, char *argv[])
{
    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-p") and (i + 1 < argc))
            fileName = argv[i + 1];

    QImage image, filteredImage;
    image.load(fileName.c_str());

    std::cout << "Copying\n";
    image.save("test_copy.png");

    std::cout << "Applying filter: Invert\n";
    TInvertFilter invFilter;
    filteredImage = invFilter.applyToImage(image);
    filteredImage.save("test_inv.png");

    std::cout << "Applying filter: GrayScale\n";
    TGrayScaleFilter grayFilter;
    filteredImage = grayFilter.applyToImage(image);
    filteredImage.save("test_gray.png");

    std::cout << "Applying filter: Sepia\n";
    TSepiaFilter sepiaFilter;
    filteredImage = sepiaFilter.applyToImage(image);
    filteredImage.save("test_sepia.png");

    std::cout << "Applying filter: Brightness(50)\n";
    TBrightnessFilter brightnessFilter(50);
    filteredImage = brightnessFilter.applyToImage(image);
    filteredImage.save("test_brightness.png");

    std::cout << "Applying filter: Blur(2)\n";
    TBlurFilter blurFilter(2);
    filteredImage = blurFilter.applyToImage(image);
    filteredImage.save("test_blur.png");

    std::cout << "Applying filter: GaussianBlur\n";
    TGaussianBlurFilter gBlurFilter;
    filteredImage = gBlurFilter.applyToImage(image);
    filteredImage.save("test_gblur.png");

    std::cout << "Applying filter: SobelY\n";
    TSobelYFilter sobelFilter;
    filteredImage = sobelFilter.applyToImage(image);
    filteredImage.save("test_sobel.png");

    std::cout << "Applying filter: Sharpness\n";
    TSharpnessFilter sharpnessFilter;
    filteredImage = sharpnessFilter.applyToImage(image);
    filteredImage.save("test_sharpness.png");

    std::cout << "Applying filter: Median(1)\n";
    TMedianFilter median1Filter(1);
    filteredImage = median1Filter.applyToImage(image);
    filteredImage.save("test_median1.png");

    std::cout << "Applying filter: Median(10)\n";
    TMedianFilter median2Filter(1);
    filteredImage = median2Filter.applyToImage(image);
    filteredImage.save("test_median10.png");

    std::cout << "Applying filter: Median(50)\n";
    TMedianFilter median3Filter(50);
    filteredImage = median3Filter.applyToImage(image);
    filteredImage.save("test_median50.png");

    return 0;
}
