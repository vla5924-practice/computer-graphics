#include "TMainWindow.h"

TMainWindow::TMainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Tomogram Visualizer");
    button = new QPushButton("Open", this);
    visualizer = new TVisualizerWidget(this);
    visualizer->move(0, 50);
    connect(button, SIGNAL(released()), this, SLOT(handleButton()));
}

TMainWindow::~TMainWindow()
{
    delete button;
    delete visualizer;
}

void TMainWindow::visualizeDataset(const char* fileName)
{
    visualizer->loadDatasetFile(fileName);
}

void TMainWindow::handleButton()
{
    button->setText("Example");
}