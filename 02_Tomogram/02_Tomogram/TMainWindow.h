#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QLineEdit>
#include <QtGui/QIntValidator>
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
    void onRadioRenderQuadsClick();
    void onRadioRenderTextureClick();
    void onRadioRenderQuadStripClick();
    void onRadioProjectionXYZClick();
    void onRadioProjectionYZXClick();
    void onRadioProjectionXZYClick();
    void onButtonSetLimitsClick();

private:
    bool autoRenderEnabled;

    QPushButton* buttonOpen;
    QPushButton* buttonRenderMode;
    QSlider* sliderCurrentLayer;
    QLabel* labelLayersCount;
    QLabel* labelCurrentLayer;
    QLabel* labelErrorMessage;
    QButtonGroup* groupRenderMode;
    QRadioButton* radioRenderQuads;
    QRadioButton* radioRenderTexture;
    QRadioButton* radioRenderQuadStrip;
    QButtonGroup* groupProjectionDir;
    QRadioButton* radioProjectionXYZ;
    QRadioButton* radioProjectionYZX;
    QRadioButton* radioProjectionXZY;
    QLineEdit* lineLimitMin;
    QLineEdit* lineLimitMax;
    QIntValidator* intValidatorLimits;
    QPushButton* buttonSetLimits;
    TVisualizerWidget* visualizer;

    void setAutoFixedSize();
    void setLabelLayersCountValue(int value);
    void setLabelCurrentLayerValue(int value);
    void setControlsVisible(bool isVisible);
    void connectButtons();
    void updateLayersCounters();
    void setErrorMessage(const char* message);
};