#include <QApplication>
#include <string>
#include <cstring>
#include "TVisualizerWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-d") && (i + 1 < argc))
            fileName = argv[i + 1];

    TVisualizerWidget visualizer(fileName.c_str());
    visualizer.resizeAuto();
    visualizer.show();

    return app.exec();
}
