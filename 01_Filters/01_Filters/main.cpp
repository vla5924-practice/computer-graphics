#include "includes.h"

int main(int argc, char *argv[])
{
    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-p") and (i + 1 < argc))
            fileName = argv[i + 1];

    QImage image;
    image.load(fileName.c_str());
    image.save("test_copy.png");

    TInvertFilter invFilter;
    QImage invImage = invFilter.applyToImage(image);
    invImage.save("test_inv.png");

    TBlurFilter blurFilter(2);
    QImage blurredImage = blurFilter.applyToImage(image);
    blurredImage.save("test_blur.png");

    return 0;
}
