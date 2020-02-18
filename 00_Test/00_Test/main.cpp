#include <QtCore/QCoreApplication>
#include "Filters.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QImage image, invertedImage, averagedImage;
    image.load("test.png", "png");
    invertedImage = image;
    inversion(invertedImage);
    invertedImage.save("test_inversion.png", "png");
    averagedImage = image;
    averaging(averagedImage);
    averagedImage.save("test_averaging.png", "png");
    return app.exec();
}
