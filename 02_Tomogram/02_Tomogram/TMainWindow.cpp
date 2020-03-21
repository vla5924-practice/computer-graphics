#include "TMainWindow.h"

TMainWindow::TMainWindow(QWidget* parent) : QMainWindow(parent)
{
    autoRenderEnabled = false;
    setWindowTitle("Tomogram Visualizer");

    openButton = new QPushButton("Open", this);
    openButton->move(5, 5);

    renderModeButton = new QPushButton("Loading", this);
    renderModeButton->move(110, 5);

    visualizer = new TVisualizerWidget(this);
    visualizer->move(5, 40);

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->move(215, 6);
    slider->setRange(0, 0);
    slider->resize(200, 30);

    labelLayersCount = new QLabel(this);
    labelLayersCount->move(420, 0);
    setLabelLayersCountValue(0);
    labelCurrentLayer = new QLabel(this);
    labelCurrentLayer->move(420, 12);
    setLabelCurrentLayerValue(0);

    connect(openButton, SIGNAL(released()), this, SLOT(handleButton()));
    connect(renderModeButton, SIGNAL(released()), this, SLOT(onRenderModeButtonClick()));
    onRenderModeButtonClick();

    setAutoFixedSize();
}

TMainWindow::~TMainWindow()
{
    delete openButton;
    delete renderModeButton;
    delete visualizer;
    delete slider;
    delete labelLayersCount;
    delete labelCurrentLayer;
}

void TMainWindow::visualizeDataset(const char* fileName)
{
    visualizer->loadDatasetFile(fileName);
    setAutoFixedSize();
    int layersCount = visualizer->getLayersCount();
    slider->setRange(1, layersCount);
    slider->setValue(1);
    setLabelCurrentLayerValue(1);
    setLabelLayersCountValue(layersCount);
}

void TMainWindow::handleButton()
{
    openButton->setText("Example");
}

void TMainWindow::onRenderModeButtonClick()
{
    if (autoRenderEnabled)
    {
        renderModeButton->setText("Auto-render: OFF");
        autoRenderEnabled = false;
        disconnect(slider, &QSlider::valueChanged, this, &TMainWindow::onSliderChange);
        connect(slider, SIGNAL(sliderReleased()), this, SLOT(onSliderChange()));
    }
    else
    {
        renderModeButton->setText("Auto-render: ON");
        autoRenderEnabled = true;
        disconnect(slider, SIGNAL(sliderReleased()), this, SLOT(onSliderChange()));
        connect(slider, &QSlider::valueChanged, this, &TMainWindow::onSliderChange);
    }
}


void TMainWindow::onSliderChange()
{
    int value = slider->value();
    visualizer->setLayerNumber(value - 1);
    setLabelCurrentLayerValue(value);
}

void TMainWindow::setAutoFixedSize()
{
    int width = visualizer->getVisWidth();
    int height = visualizer->getVisHeight() + 50;
    if (width < 600)
        width = 600;
    if (height < 600)
        height = 600;
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
