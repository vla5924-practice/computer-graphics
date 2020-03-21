#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include "TVisualizerWidget.h"

namespace Ui
{
    class TMainWindow;
}

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TMainWindow(QWidget* parent = nullptr);
    virtual ~TMainWindow();
    void visualizeDataset(const char* fileName);

private slots:
    void handleButton();

private:
    QPushButton* button;
    TVisualizerWidget* visualizer;
};