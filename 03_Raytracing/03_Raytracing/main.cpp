#include <QApplication>
#include "TShaderWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TShaderWidget w;
    w.resize(300, 300);
    w.show();
    return a.exec();
}
