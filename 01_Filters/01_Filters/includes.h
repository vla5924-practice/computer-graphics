#pragma once

/* Qt libraries */
#include <QtCore/QCoreApplication>
#include <QImage>

/* Standard libraries */
#include <string>
#include <cstring>
#include <ciso646>
#include <iostream>
#include <vector>

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
#include "TMotionBlurFilter.h"

/* Dynamic matrix filters */
#include "TMedianFilter.h"
#include "TMaximumFilter.h"

/* Morphology filters */
#include "TDilationFilter.h"
#include "TErosionFilter.h"
#include "TOpeningFilter.h"
#include "TClosingFilter.h"
#include "TTopHatFilter.h"
#include "TBlackHatFilter.h"

/* Complex filters */
#include "TGlowingEdgesFilter.h"

/* Correction filters */
#include "TLinearCorrectionFilter.h"
#include "TGrayWorldFilter.h"
#include "TPerfectReflectorFilter.h"
#include "TReferenceColorFilter.h"
#include "TGammaCorrectionFilter.h"