#include "TMainWindow.h"

TMainWindow::TMainWindow(QWidget* parent) : QMainWindow(parent)
{
    autoRenderEnabled = false;
    setWindowTitle("Tomogram Visualizer");

    openButton = new QPushButton("Open dataset", this);
    openButton->move(5, 5);

    renderModeButton = new QPushButton("Auto-Render", this);
    renderModeButton->move(110, 5);

    visualizer = new TVisualizerWidget(this);
    visualizer->move(0, 60);

    sliderCurrentLayer = new QSlider(Qt::Orientation::Horizontal, this);
    sliderCurrentLayer->move(215, 6);
    sliderCurrentLayer->setRange(0, 0);
    sliderCurrentLayer->resize(200, 30);
    sliderCurrentLayer->setVisible(false);

    labelLayersCount = new QLabel(this);
    labelLayersCount->move(420, 0);
    setLabelLayersCountValue(0);
    labelLayersCount->setVisible(false);

    labelCurrentLayer = new QLabel(this);
    labelCurrentLayer->move(420, 12);
    setLabelCurrentLayerValue(0);
    labelCurrentLayer->setVisible(false);

    labelErrorMessage = new QLabel("Dataset not opened.", this);
    labelErrorMessage->move(6, 30);

    connect(openButton, SIGNAL(released()), this, SLOT(onOpenButtonClick()));
    connect(renderModeButton, SIGNAL(released()), this, SLOT(onRenderModeButtonClick()));
    onRenderModeButtonClick();

    setAutoFixedSize();
}

TMainWindow::~TMainWindow()
{
    delete openButton;
    delete renderModeButton;
    delete visualizer;
    delete sliderCurrentLayer;
    delete labelLayersCount;
    delete labelCurrentLayer;
    delete labelErrorMessage;
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
    openButton->setDisabled(true);
    openButton->setText("Processing...");
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
            labelCurrentLayer->setVisible(true);
            labelLayersCount->setVisible(true);
            sliderCurrentLayer->setVisible(true);
            labelErrorMessage->setText("");
        }
        catch (std::exception & e)
        {
            labelErrorMessage->setText(e.what());
        }
    }
    openButton->setDisabled(false);
    openButton->setText("Open dataset");
}

void TMainWindow::onRenderModeButtonClick()
{
    if (autoRenderEnabled)
    {
        renderModeButton->setText("Auto-render: OFF");
        autoRenderEnabled = false;
        disconnect(sliderCurrentLayer, &QSlider::valueChanged, this, &TMainWindow::onSliderChange);
        connect(sliderCurrentLayer, SIGNAL(sliderReleased()), this, SLOT(onSliderChange()));
    }
    else
    {
        renderModeButton->setText("Auto-render: ON");
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
    catch (std::exception & e)
    {
        labelErrorMessage->setText(e.what());
    }
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
