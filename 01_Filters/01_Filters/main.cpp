#include "includes.h"

int main(int argc, char *argv[])
{
    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-p") and (i + 1 < argc))
            fileName = argv[i + 1];

    QImage image, filteredImage;
    image.load(fileName.c_str());

    /*std::cout << "Copying\n";
    image.save("test_copy.png");

    std::cout << "Applying filter: Invert\n";
    TInvertFilter invFilter;
    filteredImage = invFilter.applyToImage(image);
    filteredImage.save("test_inv.png");

    std::cout << "Applying filter: Rotate(20, 40, 30)\n";
    TRotateFilter rotateFilter(20, 40, 30);
    filteredImage = rotateFilter.applyToImage(image);
    filteredImage.save("test_rotate.png");

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

    std::cout << "Applying filter: Blur(3)\n";
    TBlurFilter blurFilter(3);
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
    TMedianFilter median2Filter(10);
    filteredImage = median2Filter.applyToImage(image);
    filteredImage.save("test_median10.png");

    std::cout << "Applying filter: Shift(30, 10)\n";
    TShiftFilter shiftFilter(30, 10);
    filteredImage = shiftFilter.applyToImage(image);
    filteredImage.save("test_shift.png");

    std::cout << "Applying filter: Waves\n";
    TWavesFilter wavesFilter;
    filteredImage = wavesFilter.applyToImage(image);
    filteredImage.save("test_waves.png");
    
    std::cout << "Applying filter: Motion blur(4)\n";
    TMotionBlurFilter mBlurFilter(4);
    filteredImage = mBlurFilter.applyToImage(image);
    filteredImage.save("test_mblur.png");

    std::cout << "Applying filter: Maximum(2)\n";
    TMaximumFilter maximumFilter(2);
    filteredImage = maximumFilter.applyToImage(image);
    filteredImage.save("test_max.png");
    
    std::cout << "Applying filter: Glowing Edges\n";
    TGlowingEdgesFilter glowingEdgesFilter;
    filteredImage = glowingEdgesFilter.applyToImage(image);
    filteredImage.save("test_gedges.png");*/

    std::vector<bool> morphMask = {
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1
    };

    std::vector<bool> morph2Mask = {
        0, 1, 1, 1, 0,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0
    };

    /*std::cout << "Applying filter: Dilation(2)\n";
    TDilationFilter dilationFilter(morphMask);
    filteredImage = dilationFilter.applyToImage(image);
    filteredImage.save("test_dilation.png");

    std::cout << "Applying filter: Erosion(2)\n";
    TErosionFilter erosionFilter(morphMask);
    filteredImage = erosionFilter.applyToImage(image);
    filteredImage.save("test_erosion.png");

    std::cout << "Applying filter: Opening(2)\n";
    TOpeningFilter openingFilter(morphMask);
    filteredImage = openingFilter.applyToImage(image);
    filteredImage.save("test_opening.png");

    std::cout << "Applying filter: Closing(2)\n";
    TClosingFilter closingFilter(morphMask);
    filteredImage = closingFilter.applyToImage(image);
    filteredImage.save("test_closing.png");

    std::cout << "Applying filter: TopHat(2)\n";
    TTopHatFilter topHatFilter(morphMask);
    filteredImage = topHatFilter.applyToImage(image);
    filteredImage.save("test_tophat.png");*/

    std::cout << "Applying filter: BlackHat(2)\n";
    TBlackHatFilter blackHatFilter(morph2Mask);
    filteredImage = blackHatFilter.applyToImage(image);
    filteredImage.save("test_blackhat.png");

    return 0;
}
