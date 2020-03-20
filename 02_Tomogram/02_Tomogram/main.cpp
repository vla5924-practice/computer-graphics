#include "includes.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    std::string fileName;
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-d") && (i + 1 < argc))
            fileName = argv[i + 1];

    QMainWindow w;
    w.setWindowTitle("Tomogram Visualizer");
    
    QPushButton btn("Open", &w);

    TVisualizerWidget visualizer(fileName.c_str(), &w);
    visualizer.resizeAuto();
    visualizer.move(0, btn.height() + 10);
    //visualizer.show();

    w.setFixedSize(visualizer.getVisWidth() + 50, visualizer.getVisHeight() + 50);

    //btn.connect(&btn, SIGNAL(pressed()), &btn, SLOT(doSomething()));

    w.show();

    return app.exec();
}
