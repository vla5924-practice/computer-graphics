#include <QApplication>
#include "TGLWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TGLWidget w;
    w.resize(400, 200);
    w.show();
    return app.exec();
}
