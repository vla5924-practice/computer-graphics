#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>
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
    void onOpenButtonClick();
    void onRenderModeButtonClick();
    void onSliderChange();

private:
    bool autoRenderEnabled;

    QPushButton* openButton;
    QPushButton* renderModeButton;
    QSlider* sliderCurrentLayer;
    QLabel* labelLayersCount;
    QLabel* labelCurrentLayer;
    QLabel* labelErrorMessage;
    TVisualizerWidget* visualizer;

    void setAutoFixedSize();
    void setLabelLayersCountValue(int value);
    void setLabelCurrentLayerValue(int value);
};