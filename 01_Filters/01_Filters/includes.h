#pragma once

/* Qt libraries */
#include <QtCore/QCoreApplication>
#include <QImage>

/* Standard libraries */
#include <string>
#include <cstring>
#include <ciso646>
#include <iostream>

/* Point filters */
#include "TInvertFilter.h"
#include "TGrayScaleFilter.h"
#include "TSepiaFilter.h"
#include "TBrightnessFilter.h"

/* Direct point filters */
#include "TShiftFilter.h"
#include "TWavesFilter.h"
#include "TRotateFilter.h"

/* Matrix filters */
#include "TBlurFilter.h"
#include "TGaussianBlurFilter.h"
#include "TSobelYFilter.h"
#include "TSharpnessFilter.h"
#include "TMedianFilter.h"
#include "TMotionBlurFilter.h"
#include "TMaximumFilter.h"

/* Complex filters */
#include "TGlowingEdgesFilter.h"