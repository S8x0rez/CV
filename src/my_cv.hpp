#ifndef MY_CV_HPP
#define MY_CV_HPP

#include "imgio.hpp"
#include "data.hpp"

// ----------change color-------------
void GrayScale(IMG_RGB*);
void ValueScaling(IMG_RGB*, int, int);
void GammaCorrection(IMG_RGB*, double);
void SToneCurve(IMG_RGB*, double);
void HighContrast(IMG_RGB*, double, double);
void LowContrast(IMG_RGB*, double, double);
void NegaPosiReversal(IMG_RGB*);
void Postarization(IMG_RGB*, int);
void Solarization(IMG_RGB*, int);
// void FlatteningHistogram(IMG_RGB*);
void Binarize(IMG_RGB*, int);
// void OtsuBinarize(IMG_RGB*);
void changeBrightness(IMG_HSV*, int);

// -----------high pass---------------
void PrewittFilter(IMG_RGB*, IMG_RGB*, int, int);
void SobelFilter(IMG_RGB*, IMG_RGB*, int, int);
void LaplacianFilter(IMG_RGB*, IMG_RGB*, int);

// -----------low pass----------------
void MeanFilter(IMG_RGB*, IMG_RGB*, int);
void WeightedMeanFilter(IMG_RGB*, IMG_RGB*, int);
void MedialFilter(IMG_RGB*, IMG_RGB*, int);
void GaussianFilter(IMG_RGB*, IMG_RGB*, int, double);
// void BilateralFilter(IMG_RGB*, IMG_RGB*);
void MotionBlur(IMG_RGB*, IMG_RGB*, int, int);

// -----------shape conversion----------------
// void ResizeIMG(IMG_RGB*, IMG_RGB*, double);
void AffineTransformation(IMG_RGB*, IMG_RGB*, double, double, double, double, double, double);

#endif // MY_CV_HPP
