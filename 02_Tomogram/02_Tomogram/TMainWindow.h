#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
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
    void onRenderModeButtonClick();
    void onSliderChange();

private:
    bool autoRenderEnabled;

    QPushButton* openButton;
    QPushButton* renderModeButton;
    QSlider* slider;
    QLabel* labelLayersCount;
    QLabel* labelCurrentLayer;
    TVisualizerWidget* visualizer;

    void setAutoFixedSize();
    void setLabelLayersCountValue(int value);
    void setLabelCurrentLayerValue(int value);
};