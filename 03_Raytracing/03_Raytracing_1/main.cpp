#include <qapplication.h>
#include "TShaderWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TShaderWidget w;
    w.resize(512, 512);
    w.show();
    return a.exec();
}
