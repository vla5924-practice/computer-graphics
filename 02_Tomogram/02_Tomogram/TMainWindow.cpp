#include "TMainWindow.h"

TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent), autoRenderEnabled(false)
{
    setWindowTitle("Tomogram Visualizer");
    setUpWidgets();
    connectButtons();
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
    delete labelVisSize;
    delete radioRenderQuads;
    delete radioRenderTexture;
    delete radioRenderQuadStrip;
    delete groupRenderMode;
    delete radioProjectionXYZ;
    delete radioProjectionZXY;
    delete radioProjectionYZX;
    delete groupProjectionDir;
    delete lineLimitMin;
    delete lineLimitMax;
    delete buttonSetLimits;
    delete buttonReset;
    delete intValidatorLimits;
}

void TMainWindow::visualizeDataset(const char* fileName)
{
    visualizer->loadDatasetFile(fileName);
    updateControls();
    resetLimitsLines();
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
            intValidatorLimits->setRange(visualizer->getDataMin(), visualizer->getDataMax());
            setErrorMessage("");
        }
        catch (std::exception& e)
        {
            setErrorMessage(e.what());
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
        setErrorMessage(e.what());
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

void TMainWindow::onRadioProjectionXYZClick()
{
    visualizer->setLayerNumber(0);
    visualizer->setProjectionDir(TVisualizerWidget::ProjectionDir::XYZ);
    updateControls();
}

void TMainWindow::onRadioProjectionYZXClick()
{
    visualizer->setLayerNumber(0);
    visualizer->setProjectionDir(TVisualizerWidget::ProjectionDir::YZX);
    updateControls();
}

void TMainWindow::onRadioProjectionZXYClick()
{
    visualizer->setLayerNumber(0);
    visualizer->setProjectionDir(TVisualizerWidget::ProjectionDir::ZXY);
    updateControls();
}

void TMainWindow::onButtonSetLimitsClick()
{
    int16_t min = lineLimitMin->text().toInt();
    int16_t max = lineLimitMax->text().toInt();
    if (min >= max)
    {
        setErrorMessage("Min cannot be greater than Max.");
        return;
    }
    try
    {
        visualizer->setVisibleDataLimits(min, max);
        setErrorMessage("");
    }
    catch (TVisualizerWidget::IncorrectDataLimitsError& e)
    {
        setErrorMessage(e.what());
    }
}

void TMainWindow::onButtonResetClick()
{
    resetLimitsLines();
    onButtonSetLimitsClick();
    updateLayersCounters();
}

void TMainWindow::setUpWidgets()
{
    buttonOpen = new QPushButton("&Open dataset", this);
    buttonOpen->move(5, 5);
    buttonRenderMode = new QPushButton("&Auto-Render", this);
    buttonRenderMode->move(110, 5);
    visualizer = new TVisualizerWidget(this);
    visualizer->move(0, 95);
    labelErrorMessage = new QLabel("Dataset not opened.", this);
    labelErrorMessage->move(346, 35);
    labelVisSize = new QLabel("Size: 0x0", this);
    labelVisSize->move(426, 60);
    setUpLayersCounters();
    setUpProjectionRadios();
    setUpRenderModeRadios();
    setUpLimitControls();
}

void TMainWindow::setUpLayersCounters()
{
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
}

void TMainWindow::setUpProjectionRadios()
{
    radioProjectionXYZ = new QRadioButton("XY&Z", this);
    radioProjectionXYZ->move(6, 35);
    radioProjectionXYZ->setChecked(true);
    radioProjectionZXY = new QRadioButton("ZX&Y", this);
    radioProjectionZXY->move(46, 35);
    radioProjectionYZX = new QRadioButton("YZ&X", this);
    radioProjectionYZX->move(86, 35);
    groupProjectionDir = new QButtonGroup(this);
    groupProjectionDir->addButton(radioProjectionXYZ);
    groupProjectionDir->addButton(radioProjectionZXY);
    groupProjectionDir->addButton(radioProjectionYZX);
}

void TMainWindow::setUpRenderModeRadios()
{
    radioRenderQuads = new QRadioButton("&Quads", this);
    radioRenderQuads->move(146, 35);
    radioRenderQuads->setChecked(true);
    radioRenderTexture = new QRadioButton("&Texture", this);
    radioRenderTexture->move(206, 35);
    radioRenderQuadStrip = new QRadioButton("Quad&Strip", this);
    radioRenderQuadStrip->move(266, 35);
    groupRenderMode = new QButtonGroup(this);
    groupRenderMode->addButton(radioRenderQuads);
    groupRenderMode->addButton(radioRenderTexture);
    groupRenderMode->addButton(radioRenderQuadStrip);
}

void TMainWindow::setUpLimitControls()
{
    intValidatorLimits = new QIntValidator(this);
    lineLimitMin = new QLineEdit(this);
    lineLimitMin->setPlaceholderText("Min");
    lineLimitMin->move(6, 60);
    lineLimitMin->setValidator(intValidatorLimits);
    lineLimitMax = new QLineEdit(this);
    lineLimitMax->setPlaceholderText("Max");
    lineLimitMax->move(111, 60);
    lineLimitMax->setValidator(intValidatorLimits);
    buttonSetLimits = new QPushButton("Apply limits", this);
    buttonSetLimits->move(216, 60);
    buttonReset = new QPushButton("&Reset", this);
    buttonReset->move(321, 60);
}

void TMainWindow::setAutoFixedSize()
{
    int width = visualizer->getVisWidth();
    int height = visualizer->getVisHeight() + 95;
    if (width < 512)
        width = 512;
    if (height < 95)
        height = 95;
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
    radioProjectionXYZ->setVisible(isVisible);
    radioProjectionZXY->setVisible(isVisible);
    radioProjectionYZX->setVisible(isVisible);
    radioRenderQuads->setVisible(isVisible);
    radioRenderTexture->setVisible(isVisible);
    radioRenderQuadStrip->setVisible(isVisible);
    lineLimitMin->setVisible(isVisible);
    lineLimitMax->setVisible(isVisible);
    buttonSetLimits->setVisible(isVisible);
    buttonReset->setVisible(isVisible);
    labelVisSize->setVisible(isVisible);
}

void TMainWindow::connectButtons()
{
    connect(buttonOpen, SIGNAL(released()), this, SLOT(onOpenButtonClick()));
    connect(buttonRenderMode, SIGNAL(released()), this, SLOT(onRenderModeButtonClick()));
    connect(radioRenderQuads, SIGNAL(released()), this, SLOT(onRadioRenderQuadsClick()));
    connect(radioRenderTexture, SIGNAL(released()), this, SLOT(onRadioRenderTextureClick()));
    connect(radioRenderQuadStrip, SIGNAL(released()), this, SLOT(onRadioRenderQuadStripClick()));
    connect(radioProjectionXYZ, SIGNAL(released()), this, SLOT(onRadioProjectionXYZClick()));
    connect(radioProjectionZXY, SIGNAL(released()), this, SLOT(onRadioProjectionZXYClick()));
    connect(radioProjectionYZX, SIGNAL(released()), this, SLOT(onRadioProjectionYZXClick()));
    connect(buttonSetLimits, SIGNAL(released()), this, SLOT(onButtonSetLimitsClick()));
    connect(buttonReset, SIGNAL(released()), this, SLOT(onButtonResetClick()));
}

void TMainWindow::updateLayersCounters()
{
    int layersCount = visualizer->getLayersCount();
    sliderCurrentLayer->setRange(1, layersCount);
    sliderCurrentLayer->setValue(1);
    setLabelCurrentLayerValue(1);
    setLabelLayersCountValue(layersCount);
}

void TMainWindow::updateLabelVisSize()
{
    int width = visualizer->getVisWidth();
    int height = visualizer->getVisHeight();
    setLabelVisSize(width, height);
}

void TMainWindow::updateControls()
{
    setAutoFixedSize();
    updateLayersCounters();
    updateLabelVisSize();
}

void TMainWindow::resetLimitsLines()
{
    lineLimitMin->setText(QString::number(visualizer->getDataMin()));
    lineLimitMax->setText(QString::number(visualizer->getDataMax()));
}

void TMainWindow::setErrorMessage(const char* message)
{
    labelErrorMessage->setText(message);
}

void TMainWindow::setLabelVisSize(int width, int height)
{
    QString text = QString("Size: ") + QString::number(width) + "x" + QString::number(height);
    labelVisSize->setText(text);
}
