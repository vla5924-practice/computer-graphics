#include "TMainWindow.h"

TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent), autoRenderEnabled(false)
{
    setWindowTitle("Tomogram Visualizer");

    buttonOpen = new QPushButton("&Open dataset", this);
    buttonOpen->move(5, 5);

    buttonRenderMode = new QPushButton("&Auto-Render", this);
    buttonRenderMode->move(110, 5);

    visualizer = new TVisualizerWidget(this);
    visualizer->move(0, 60);

    sliderCurrentLayer = new QSlider(Qt::Orientation::Horizontal, this);
    sliderCurrentLayer->move(215, 6);
    sliderCurrentLayer->setRange(0, 0);
    sliderCurrentLayer->resize(200, 30);

    labelLayersCount = new QLabel(this);
    labelLayersCount->move(420, 0);
    setLabelLayersCountValue(0);

    labelCurrentLayer = new QLabel(this);
    labelCurrentLayer->move(420, 12);
    setLabelCurrentLayerValue(0);

    labelErrorMessage = new QLabel("Dataset not opened.", this);
    labelErrorMessage->move(6, 30);

    radioRenderQuads = new QRadioButton("&Quads", this);
    radioRenderQuads->move(300, 30);
    radioRenderQuads->setChecked(true);
    radioRenderTexture = new QRadioButton("&Texture", this);
    radioRenderTexture->move(360, 30);
    radioRenderQuadStrip = new QRadioButton("Quad&Strip", this);
    radioRenderQuadStrip->move(420, 30);

    connect(buttonOpen,           SIGNAL(released()), this, SLOT(onOpenButtonClick())          );
    connect(buttonRenderMode,     SIGNAL(released()), this, SLOT(onRenderModeButtonClick())    );
    connect(radioRenderQuads,     SIGNAL(released()), this, SLOT(onRadioRenderQuadsClick())    );
    connect(radioRenderTexture,   SIGNAL(released()), this, SLOT(onRadioRenderTextureClick())  );
    connect(radioRenderQuadStrip, SIGNAL(released()), this, SLOT(onRadioRenderQuadStripClick()));

    onRenderModeButtonClick();
    setControlsVisible(false);
    setAutoFixedSize();
}

TMainWindow::~TMainWindow()
{
    delete buttonOpen;
    delete buttonRenderMode;
    delete visualizer;
    delete sliderCurrentLayer;
    delete labelLayersCount;
    delete labelCurrentLayer;
    delete labelErrorMessage;
    delete radioRenderQuads;
    delete radioRenderTexture;
    delete radioRenderQuadStrip;
}

void TMainWindow::visualizeDataset(const char* fileName)
{
    visualizer->loadDatasetFile(fileName);
    setAutoFixedSize();
    int layersCount = visualizer->getLayersCount();
    sliderCurrentLayer->setRange(1, layersCount);
    sliderCurrentLayer->setValue(1);
    setLabelCurrentLayerValue(1);
    setLabelLayersCountValue(layersCount);
}

void TMainWindow::onOpenButtonClick()
{
    buttonOpen->setDisabled(true);
    buttonOpen->setText("Processing...");
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Dataset binaries (*.bin)");
    if (dialog.exec())
    {
        QStringList fileNames = dialog.selectedFiles();
        std::string fileName = fileNames.at(0).toStdString();
        try
        {
            visualizeDataset(fileName.c_str());
            setControlsVisible(true);
            labelErrorMessage->setText("");
        }
        catch (std::exception & e)
        {
            labelErrorMessage->setText(e.what());
        }
    }
    buttonOpen->setDisabled(false);
    buttonOpen->setText("&Open dataset");
}

void TMainWindow::onRenderModeButtonClick()
{
    if (autoRenderEnabled)
    {
        buttonRenderMode->setText("&Auto-render: OFF");
        autoRenderEnabled = false;
        disconnect(sliderCurrentLayer, &QSlider::valueChanged, this, &TMainWindow::onSliderChange);
        connect(sliderCurrentLayer, SIGNAL(sliderReleased()), this, SLOT(onSliderChange()));
    }
    else
    {
        buttonRenderMode->setText("&Auto-render: ON");
        autoRenderEnabled = true;
        disconnect(sliderCurrentLayer, SIGNAL(sliderReleased()), this, SLOT(onSliderChange()));
        connect(sliderCurrentLayer, &QSlider::valueChanged, this, &TMainWindow::onSliderChange);
    }
}


void TMainWindow::onSliderChange()
{
    try
    {
        int value = sliderCurrentLayer->value();
        visualizer->setLayerNumber(value - 1);
        setLabelCurrentLayerValue(value);
    }
    catch (std::exception& e)
    {
        labelErrorMessage->setText(e.what());
    }
}

void TMainWindow::onRadioRenderQuadsClick()
{
    visualizer->setRenderMode(TVisualizerWidget::RenderMode::Quads);
}

void TMainWindow::onRadioRenderTextureClick()
{
    visualizer->setRenderMode(TVisualizerWidget::RenderMode::Texture);
}

void TMainWindow::onRadioRenderQuadStripClick()
{
    visualizer->setRenderMode(TVisualizerWidget::RenderMode::QuadStrip);
}

void TMainWindow::setAutoFixedSize()
{
    int width = visualizer->getVisWidth();
    int height = visualizer->getVisHeight() + 60;
    if (width < 512)
        width = 512;
    if (height < 60)
        height = 60;
    setFixedSize(width, height);
}

void TMainWindow::setLabelLayersCountValue(int value)
{
    labelLayersCount->setText(("Layers count: " + std::to_string(value)).c_str());
}

void TMainWindow::setLabelCurrentLayerValue(int value)
{
    labelCurrentLayer->setText(("Current layer: " + std::to_string(value)).c_str());
}

void TMainWindow::setControlsVisible(bool isVisible)
{
    buttonRenderMode->setVisible(isVisible);
    labelCurrentLayer->setVisible(isVisible);
    labelLayersCount->setVisible(isVisible);
    sliderCurrentLayer->setVisible(isVisible);
    radioRenderQuads->setVisible(isVisible);
    radioRenderTexture->setVisible(isVisible);
    radioRenderQuadStrip->setVisible(isVisible);
}
