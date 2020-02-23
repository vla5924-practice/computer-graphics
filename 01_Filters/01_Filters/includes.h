#pragma once

/* Qt libraries */
#include <QtCore/QCoreApplication>
#include <QImage>

/* Standard libraries */
#include <string>
#include <cstring>
#include <ciso646>

/* Point filters */
#include "TInvertFilter.h"
#include "TGrayScaleFilter.h"
#include "TSepiaFilter.h"
#include "TBrightnessFilter.h"

/* Matrix filters */
#include "TBlurFilter.h"
#include "TGaussianBlurFilter.h"
#include "TSobelYFilter.h"
#include "TSharpnessFilter.h"