#include "my_cv.hpp"

void GrayScale(IMG_RGB *img)
{
    int width, height;
    uchar value;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){

            // BT.709
            value = RoundingUC(0.2126 * (double)img->R[j + k * width] + 0.7152 * (double)img->G[j + k * width] + 0.0722 * (double)img->B[j + k * width]);

            // BT.601
            // value = RoundingUC(0.2990 * (double)img->R[j + k * width] + 0.587 * (double)img->G[j + k * width] + 0.114 * (double)img->B[j + k * width]);

            img->R[j + k * width] = value;
            img->G[j + k * width] = value;
            img->B[j + k * width] = value;
        }
    }
}

void ValueScaling(IMG_RGB *img, int a, int b)
{
    int width, height;
    int x;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img->R[j + k * width];
            img->R[j + k * width] = RoundingUC(a * x + b);

            x = img->G[j + k * width];
            img->G[j + k * width] = RoundingUC(a * x + b);

            x = img->B[j + k * width];
            img->B[j + k * width] = RoundingUC(a * x + b);
        }
    }
}

void GammaCorrection(IMG_RGB *img, double gamma)
{
    int width, height;
    double x;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img->R[j + k * width];
            img->R[j + k * width] = RoundingUC(pow(x / 255, gamma) * 255);

            x = img->G[j + k * width];
            img->G[j + k * width] = RoundingUC(pow(x / 255, gamma) * 255);

            x = img->B[j + k * width];
            img->B[j + k * width] = RoundingUC(pow(x / 255, gamma) * 255);
        }
    }
}

void SToneCurve(IMG_RGB *img, double p)
{
    int width, height;
    double x;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = (double)img->R[j + k * width];
            img->R[j + k * width] = RoundingUC(255 / (1 + exp(p * (-x + 128))));

            x = (double)img->G[j + k * width];
            img->G[j + k * width] = RoundingUC(255 / (1 + exp(p * (-x + 128))));

            x = (double)img->B[j + k * width];
            img->B[j + k * width] = RoundingUC(255 / (1 + exp(p * (-x + 128))));
        }
    }
}

void HighContrast(IMG_RGB *img, double a, double b)
{
    if (a >= b) {
        cout << "HighContrast: wrong range (b <= a)" << endl;
        return;
    }

    int width, height;
    double x;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = (double)img->R[j + k * width];
            img->R[j + k * width] = RoundingUC(255 * (x - a) / (b - a));

            x = (double)img->G[j + k * width];
            img->G[j + k * width] = RoundingUC(255 * (x - a) / (b - a));

            x = (double)img->B[j + k * width];
            img->B[j + k * width] = RoundingUC(255 * (x - a) / (b - a));
        }
    }
}

void LowContrast(IMG_RGB *img, double a, double b)
{
    if (a >= b) {
        cout << "LowContrast: wrong range (b <= a)" << endl;
        return;
    }

    int width, height;
    double x;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img->R[j + k * width];
            img->R[j + k * width] = RoundingUC((b - a) / 255 * x + a);

            x = img->G[j + k * width];
            img->G[j + k * width] = RoundingUC((b - a) / 255 * x + a);

            x = img->B[j + k * width];
            img->B[j + k * width] = RoundingUC((b - a) / 255 * x + a);
        }
    }
}

void NegaPosiInversion(IMG_RGB *img)
{
    int width, height;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            img->R[j + k * width] = 255 - img->R[j + k * width];
            img->G[j + k * width] = 255 - img->G[j + k * width];
            img->B[j + k * width] = 255 - img->B[j + k * width];
        }
    }

}

void Postarization(IMG_RGB *img, int lv)
{
    int width, height;
    int band;

    width = img->width;
    height = img->height;
    band = 255 / lv;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            img->R[j + k * width] = img->R[j + k * width] / band * band;
            img->G[j + k * width] = img->G[j + k * width] / band * band;
            img->B[j + k * width] = img->B[j + k * width] / band * band;
        }
    }
}

void Solarization(IMG_RGB *img, int a)
{
    int width, height;
    int value;
    int flag = 255 / a;

    width = img->width;
    height = img->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            value = img->R[j + k * width];
            if ((value / flag) % 2) img->R[j + k * width] = RoundingUC(255 - value * a - 255 * (value / flag));
            else img->R[j + k * width] = RoundingUC(value * a - 255 * (value / flag));

            value = img->G[j + k * width];
            if ((value / flag) % 2) img->G[j + k * width] = RoundingUC(255 - value * a - 255 * (value / flag));
            else img->G[j + k * width] = RoundingUC(value * a - 255 * (value / flag));
            
            value = img->B[j + k * width];
            if ((value / flag) % 2) img->B[j + k * width] = RoundingUC(255 - value * a - 255 * (value / flag));
            else img->B[j + k * width] = RoundingUC(value * a - 255 * (value / flag));
        }
    }
}


void Binarize(IMG_RGB *img, int threshold)
{
    IMG_HSV *tmp = new IMG_HSV;

    int width, height;

    width = img->width;
    height = img->height;

    AllocImgHSV(tmp, width, height);
    RGB2HSV(tmp, img);

    for (int k = 0; k < tmp->height; k++){
        for (int j = 0; j < tmp->width; j++){
            if (tmp->V[j + k * tmp->width] >= threshold) {
                img->R[j + k * img->width] = 255;
                img->G[j + k * img->width] = 255;
                img->B[j + k * img->width] = 255;
            }
            else {
                img->R[j + k * img->width] = 0;
                img->G[j + k * img->width] = 0;
                img->B[j + k * img->width] = 0;
            }
        }
    }

    Free(tmp);
}

void ChangeBrightness(IMG_RGB *img, int x)
{
    IMG_HSV *tmp = new IMG_HSV;

    int width, height;
    int value;

    width = img->width;
    height = img->height;

    AllocImgHSV(tmp, width, height);
    RGB2HSV(tmp, img);

    for (int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            value = tmp->V[j + k * width] + x;
            tmp->V[j + k * width] = RoundingUC(value);
        }
    }

    HSV2RGB(img, tmp);
    Free(tmp);
}

void PrewittFilter(IMG_RGB *img_in, int mode, int d)  // in: gray scale
{
    IMG_HSV *tmp = new IMG_HSV;
    int width, height;
    int value;

    width = img_in->width;
    height = img_in->height;

    AllocImgHSV(tmp, width, height);
    RGB2HSV(tmp, img_in);

    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            value = 0;
            if (mode != 1) {    // Vertical edge ditection
                value += -1 * tmp->V[(j - 1) + (k - 1) * width] + 1 * tmp->V[(j + 1) + (k - 1) * width]
                         -1 * tmp->V[(j - 1) + k * width]       + 1 * tmp->V[(j + 1) + k * width]
                         -1 * tmp->V[(j - 1) + (k + 1) * width] + 1 * tmp->V[(j + 1) + (k + 1) * width];
            }
            if (mode !=2) {    // Horisontal edge ditection
                value += -1 * tmp->V[(j - 1) + (k - 1) * width] -2 * tmp->V[j + (k - 1) * width] -1 * tmp->V[(j + 1) + (k - 1) * width]
                         +1 * tmp->V[(j - 1) + (k + 1) * width] +2 * tmp->V[j + (k + 1) * width] +1 * tmp->V[(j + 1) + (k + 1) * width];
            }
            value = d * abs(value);
            img_in->R[j + k * width] = RoundingUC(value);
            img_in->G[j + k * width] = RoundingUC(value);
            img_in->B[j + k * width] = RoundingUC(value);
        }
    }

    Free(tmp);
}

void SobelFilter(IMG_RGB *img_in, int mode, int d)  // in: gray scale
{
    IMG_HSV *tmp = new IMG_HSV;
    int width, height;
    int value;

    width = img_in->width;
    height = img_in->height;

    AllocImgHSV(tmp, width, height);
    RGB2HSV(tmp, img_in);

    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            value = 0;
            if (mode != 1) {    // Vertical edge ditection
                value += -1 * tmp->V[(j - 1) + (k - 1) * width] + 1 * tmp->V[(j + 1) + (k - 1) * width]
                         -2 * tmp->V[(j - 1) + k * width]       + 2 * tmp->V[(j + 1) + k * width]
                         -1 * tmp->V[(j - 1) + (k + 1) * width] + 1 * tmp->V[(j + 1) + (k + 1) * width];
            }
            if (mode !=2) {    // Horisontal edge ditection
                value += -1 * tmp->V[(j - 1) + (k - 1) * width] -2 * tmp->V[j + (k - 1) * width] -1 * tmp->V[(j + 1) + (k - 1) * width]
                         +1 * tmp->V[(j - 1) + (k + 1) * width] +2 * tmp->V[j + (k + 1) * width] +1 * tmp->V[(j + 1) + (k + 1) * width];
            }
            value = d * abs(value);
            img_in->R[j + k * width] = RoundingUC(value);
            img_in->G[j + k * width] = RoundingUC(value);
            img_in->B[j + k * width] = RoundingUC(value);
        }
    }

    Free(tmp);
}

void LaplacianFilter(IMG_RGB *img_in, int direction, int d)  // in: gray scale
{
    IMG_HSV *tmp = new IMG_HSV;

    int width, height;

    width = img_in->width;
    height = img_in->height;

    AllocImgHSV(tmp, width, height);
    RGB2HSV(tmp, img_in);

    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            int value;
            if (direction == 4) {
                value =                                   -1 * tmp->V[j + (k - 1) * width]
                        -1 * tmp->V[(j - 1) + k * width] + 4 * tmp->V[j + k * width]       -1 * tmp->V[(j + 1) + k * width]
                                                          -1 * tmp->V[j + (k + 1) * width];
            }
            else {
                value = -1 * tmp->V[(j - 1) + (k - 1) * width] -1 * tmp->V[j + (k - 1) * width] -1 * tmp->V[(j + 1) + (k - 1) * width]
                        -1 * tmp->V[(j - 1) + k * width]      + 8 * tmp->V[j + k * width]       -1 * tmp->V[(j + 1) + k * width]
                        -1 * tmp->V[(j - 1) + (k + 1) * width] -1 * tmp->V[j + (k + 1) * width] -1 * tmp->V[(j + 1) + (k + 1) * width];
            }
            img_in->R[j + k * width] = RoundingUC(d * value);
            img_in->G[j + k * width] = RoundingUC(d * value);
            img_in->B[j + k * width] = RoundingUC(d * value);
        }
    }

    Free(tmp);
}

void LaplacianFilterRGB(IMG_RGB *img_in, int direction, int d)  // in: gray scale
{
    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;

    width = img_in->width;
    height = img_in->height;

    AllocImgRGB(img_rgb, width, height);

    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            int value[3] = {0, 0, 0};
            if (direction == 4) {
                value[0] =                                      -1 * img_in->R[j + (k - 1) * width]
                           -1 * img_in->R[(j - 1) + k * width] + 4 * img_in->R[j + k * width]       -1 * img_in->R[(j + 1) + k * width]
                                                                -1 * img_in->R[j + (k + 1) * width];

                value[1] =                                      -1 * img_in->G[j + (k - 1) * width]
                           -1 * img_in->G[(j - 1) + k * width] + 4 * img_in->G[j + k * width]       -1 * img_in->G[(j + 1) + k * width]
                                                                -1 * img_in->G[j + (k + 1) * width];

                value[2] =                                      -1 * img_in->B[j + (k - 1) * width]
                           -1 * img_in->B[(j - 1) + k * width] + 4 * img_in->B[j + k * width]       -1 * img_in->B[(j + 1) + k * width]
                                                                -1 * img_in->B[j + (k + 1) * width];
            }
            else {
                value[0] = -1 * img_in->R[(j - 1) + (k - 1) * width] -1 * img_in->R[j + (k - 1) * width] -1 * img_in->R[(j + 1) + (k - 1) * width]
                           -1 * img_in->R[(j - 1) + k * width]      + 8 * img_in->R[j + k * width]       -1 * img_in->R[(j + 1) + k * width]
                           -1 * img_in->R[(j - 1) + (k + 1) * width] -1 * img_in->R[j + (k + 1) * width] -1 * img_in->R[(j + 1) + (k + 1) * width];

                value[1] = -1 * img_in->G[(j - 1) + (k - 1) * width] -1 * img_in->G[j + (k - 1) * width] -1 * img_in->G[(j + 1) + (k - 1) * width]
                           -1 * img_in->G[(j - 1) + k * width]      + 8 * img_in->G[j + k * width]       -1 * img_in->G[(j + 1) + k * width]
                           -1 * img_in->G[(j - 1) + (k + 1) * width] -1 * img_in->G[j + (k + 1) * width] -1 * img_in->G[(j + 1) + (k + 1) * width];

                value[2] = -1 * img_in->B[(j - 1) + (k - 1) * width] -1 * img_in->B[j + (k - 1) * width] -1 * img_in->B[(j + 1) + (k - 1) * width]
                           -1 * img_in->B[(j - 1) + k * width]      + 8 * img_in->B[j + k * width]       -1 * img_in->B[(j + 1) + k * width]
                           -1 * img_in->B[(j - 1) + (k + 1) * width] -1 * img_in->B[j + (k + 1) * width] -1 * img_in->B[(j + 1) + (k + 1) * width];
            }
            img_rgb->R[j + k * width] = RoundingUC(d * value[0]);
            img_rgb->G[j + k * width] = RoundingUC(d * value[1]);
            img_rgb->B[j + k * width] = RoundingUC(d * value[2]);
        }
    }
    
    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

void MeanFilter(IMG_RGB *img_in, int size)
{
    if (size % 2 == 0) {
        cout << "MeanFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "MeanFilter: filter size error (size is even number)" << endl;
        return;
    }

    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;
    int r;

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

    AllocImgRGB(img_rgb, width, height);
    CopyRGB(img_rgb, img_in);

    for (int k = r; k < height - r; k++){
        for (int j = r; j < width - r; j++){
            int value[3] = {0, 0, 0};
            for (int kk = -r; kk <= r; kk++) {
                for (int jj = -r; jj <= r; jj++) {
                    value[0] += img_in->R[(j + jj) + (k + kk) * width];
                    value[1] += img_in->G[(j + jj) + (k + kk) * width];
                    value[2] += img_in->B[(j + jj) + (k + kk) * width];
                }
            }
            img_rgb->R[j + k * width] = RoundingUC(value[0] / (size*size));
            img_rgb->G[j + k * width] = RoundingUC(value[1] / (size*size));
            img_rgb->B[j + k * width] = RoundingUC(value[2] / (size*size));
        }
    }
    
    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

void WeightedMeanFilter(IMG_RGB *img_in, int add)
{
    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;
    int value[3];

    width = img_in->width;
    height = img_in->height;

    AllocImgRGB(img_rgb, width, height);

    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            value[0] =   img_in->R[(j - 1) + (k - 1) * width] +             img_in->R[j + (k - 1) * width] + img_in->R[(j + 1) + (k - 1) * width]
                       + img_in->R[(j - 1) + k * width]       + (add + 1) * img_in->R[j + k * width]       + img_in->R[(j + 1) + k * width]
                       + img_in->R[(j - 1) + (k + 1) * width] +             img_in->R[j + (k + 1) * width] + img_in->R[(j + 1) + (k + 1) * width];

            value[1] =   img_in->G[(j - 1) + (k - 1) * width] +             img_in->G[j + (k - 1) * width] + img_in->G[(j + 1) + (k - 1) * width]
                       + img_in->G[(j - 1) + k * width]       + (add + 1) * img_in->G[j + k * width]       + img_in->G[(j + 1) + k * width]
                       + img_in->G[(j - 1) + (k + 1) * width] +             img_in->G[j + (k + 1) * width] + img_in->G[(j + 1) + (k + 1) * width];

            value[2] =   img_in->B[(j - 1) + (k - 1) * width] +             img_in->B[j + (k - 1) * width] + img_in->B[(j + 1) + (k - 1) * width]
                       + img_in->B[(j - 1) + k * width]       + (add + 1) * img_in->B[j + k * width]       + img_in->B[(j + 1) + k * width]
                       + img_in->B[(j - 1) + (k + 1) * width] +             img_in->B[j + (k + 1) * width] + img_in->B[(j + 1) + (k + 1) * width];

            img_rgb->R[j + k * width] = RoundingUC(value[0] / (9 + add));
            img_rgb->G[j + k * width] = RoundingUC(value[1] / (9 + add));
            img_rgb->B[j + k * width] = RoundingUC(value[2] / (9 + add));
        }
    }
    
    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

void MedianFilter(IMG_RGB *img_in, int size)
{
    if (size % 2 == 0) {
        cout << "MedianFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "MedianFilter: filter size error (size is even number)" << endl;
        return;
    }

    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;
    int r, median;

    int **array = new int*[3];
    for (int i = 0; i < 3; i++) {
        array[i] = new int[size * size];
    }

    width = img_in->width;
    height = img_in->height;
    r = size / 2;
    median = size * size / 2 + 1;

    AllocImgRGB(img_rgb, width, height);

    for (int k = r; k < height - r; k++){
        for (int j = r; j < width - r; j++){
            for (int kk = -r; kk <= r; kk++) {
                for (int jj = -r; jj <= r; jj++) {
                    array[0][(jj + r) + (kk + r) * size] = img_in->R[(j + jj) + (k + kk) * width];
                    array[1][(jj + r) + (kk + r) * size] = img_in->G[(j + jj) + (k + kk) * width];
                    array[2][(jj + r) + (kk + r) * size] = img_in->B[(j + jj) + (k + kk) * width];
                }
            }

            sort(array[0], array[0] + size * size);
            sort(array[1], array[1] + size * size);
            sort(array[2], array[2] + size * size);
            img_rgb->R[j + k * width] = array[0][median];
            img_rgb->G[j + k * width] = array[1][median];
            img_rgb->B[j + k * width] = array[2][median];
        }
    }

    for (int i = 0; i < 3; i++) {
        delete[] array[i];
    }
    delete[] array;
    
    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

void GaussianFilter(IMG_RGB *img_in, int size, double sigma)
{
    if (size % 2 == 0) {
        cout << "GaussianFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "GaussianFilter: filter size error (size is even number)" << endl;
        return;
    }

    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;
    int r;
    double *array = new double[size * size];
    double array_sum = 0;
    double PiSigma2 = 2 * PI * pow(sigma, 2.);

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

    AllocImgRGB(img_rgb, width, height);
    CopyRGB(img_rgb, img_in);

    for (int k = -r; k <= r; k++) {
        for (int j = -r; j <= r; j++) {
            array[(j + r) + (k + r) * size] = exp(-(pow(j, 2) + pow(k, 2)) / (2 * pow(sigma, 2.))) / (2 * PI * pow(sigma, 2.));
            array_sum +=exp(-(pow(j, 2) + pow(k, 2)) / (2 * pow(sigma, 2.)));
        }
    }

    for (int k = r; k < height - r; k++) {
        for (int j = r; j < width - r; j++) {
            double value[3] = {0, 0, 0};
            for (int kk = -r; kk <= r; kk++) {
                for (int jj = -r; jj <= r; jj++) {
                    value[0] += img_in->R[(j + jj) + (k + kk) * width] * array[(jj + r) + (kk + r) * size] * (PiSigma2 / array_sum);
                    value[1] += img_in->G[(j + jj) + (k + kk) * width] * array[(jj + r) + (kk + r) * size] * (PiSigma2 / array_sum);
                    value[2] += img_in->B[(j + jj) + (k + kk) * width] * array[(jj + r) + (kk + r) * size] * (PiSigma2 / array_sum);
                }
            }

            img_rgb->R[j + k * width] = RoundingUC(value[0]);
            img_rgb->G[j + k * width] = RoundingUC(value[1]);
            img_rgb->B[j + k * width] = RoundingUC(value[2]);
        }
    }

    delete[] array;
    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

void MotionBlur(IMG_RGB *img_in, int size, int direction)
{
    IMG_RGB *img_rgb = new IMG_RGB;

    int width, height;
    int r;

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

    AllocImgRGB(img_rgb, width, height);

    if (direction == 90) {
        if (height < size) {
            cout << "MotionBlur: filter size error (height < size)" << endl;
        }
        for (int k = r; k < height - r; k++) {
            for (int j = 0; j < width; j++) {
                int value[3] = {0, 0, 0};
                for (int kk = -r; kk <= r; kk++) {
                    value[0] += img_in->R[j + (k + kk) * width];
                    value[1] += img_in->G[j + (k + kk) * width];
                    value[2] += img_in->B[j + (k + kk) * width];
                }

                img_rgb->R[j + k * width] = RoundingUC(value[0] / (size << 2));
                img_rgb->G[j + k * width] = RoundingUC(value[1] / (size << 2));
                img_rgb->B[j + k * width] = RoundingUC(value[2] / (size << 2));
            }
        }
    }
    else {
        if (width < size) {
            cout << "MotionBlur: filter size error (width < size)" << endl;
        }
        for (int k = 0; k < height; k++) {
            for (int j = r; j < width - r; j++) {
                int value[3] = {0, 0, 0};
                for (int jj = -r; jj <= r; jj++) {
                    value[0] += img_in->R[(j + jj) + k * width];
                    value[1] += img_in->G[(j + jj) + k * width];
                    value[2] += img_in->B[(j + jj) + k * width];
                }

                img_rgb->R[j + k * width] = RoundingUC(value[0] / size);
                img_rgb->G[j + k * width] = RoundingUC(value[1] / size);
                img_rgb->B[j + k * width] = RoundingUC(value[2] / size);
            }
        }
    }

    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}

/* *void ResizeIMG(IMG_RGB *img_in, double scale)
{
    IMG_RGB *tmp = new IMG_RGB;
    int width, height;
    
    width = img->width * scale;
    height = img->height * scale;

    AllocImgRGB(tmp, width, height);

    if (scale < 1) {

    }
    else if (scale > 1) {

    }
    else return img;

    Free(img);
    return tmp;
}*/

void AffineTransformation(IMG_RGB *img_in, double a, double b, double c, double d, double e, double f)
{
    auto BicubicSinc = [](double t) -> double {
        double value, at;

        at = fabs(t);
        if (at <= 1) {
            value = 1 - 2 * t*t + t*t*t;
        }
        else if (at > 2) {
            value = 0;
        }
        else {
            value = 4 - 8 * t + 5 * t*t - t*t*t;
        }
        return value;
    };

    IMG_RGB *img_rgb = new IMG_RGB;

    int j, k;
	int jj, kk;
	int width, height;
	int w2, h2;
	double Det;
	double jf, kf;
	int j0, k0;
	int loop, loopj, loopk, loopw;
	double d0x[4], d0y[4];
	int fR[4][4], fG[4][4], fB[4][4];
	double hy[4], hx[4];
	double sumR, sumG, sumB;
    double workR[4], workG[4], workB[4];

	width = img_in->width;
	height = img_in->height;
	w2 = width / 2;
	h2 = height / 2;

    AllocImgRGB(img_rgb, width, height);

	for (k = 0; k<height; k++){       /* 変換後の画像上でスキャン */
		for (j = 0; j<width; j++){    /* 変換後の画像上でスキャン */

			/* 回転前の座標値に変換 (in case of 0<r<90) */

			Det = a*d - b*c;
			jf = (d*(j - w2 - e) - b*(k - h2 - f)) / Det + w2;
			kf = (-c*(j - w2 - e) + a*(k - h2 - f)) / Det + h2;

			jf = RoundingInt(jf*100000.0) / 100000.0;   /* 演算誤差修正のための四捨五入 */
			kf = RoundingInt(kf*100000.0) / 100000.0;   /* 演算誤差修正のための四捨五入 */

			if (jf<0 || jf>(width - 1) || kf<0 || kf>(height - 1)) continue; /* 処理対象領域外 */

			/* --- by bicubic interpolation ----------------------*/

			k0 = (int)kf;   // 補間座標に対して左上に存在する入力画像の画素位置座標
			d0y[1] = kf - k0; d0y[0] = 1 + kf - k0; d0y[2] = 1 - (kf - k0); d0y[3] = 2 - (kf - k0);   // 4つの実在画素位置座標までの距離（垂直）
			for (loop = 0; loop <= 3; loop++){
				hy[loop] = BicubicSinc(d0y[loop]);
			}

			j0 = (int)jf;   // 補間座標に対して左上に存在する入力画像の画素位置座標
			d0x[1] = jf - j0; d0x[0] = 1 + jf - j0; d0x[2] = 1 - (jf - j0); d0x[3] = 2 - (jf - j0);   // 4つの実在画素位置座標までの距離（水平）
			for (loop = 0; loop <= 3; loop++){
				hx[loop] = BicubicSinc(d0x[loop]);
			}

			for (loopk = -1; loopk <= 2; loopk++){
				kk = k0 + loopk;
				if (kk<0) { kk = 0; }
				else if (kk>(height - 1)) { kk = height - 1; }
				for (loopj = -1; loopj <= 2; loopj++){
					jj = j0 + loopj;
					if (jj<0) { jj = 0; }
					else if (jj>(width - 1)) { jj = width - 1; }
					fR[loopj + 1][loopk + 1] = img_in->R[jj + kk*width];    /* 補間に使う画素を4×4行列fY[4][4]に代入 */
					fG[loopj + 1][loopk + 1] = img_in->G[jj + kk*width];    /* 補間に使う画素を4×4行列fY[4][4]に代入 */
					fB[loopj + 1][loopk + 1] = img_in->B[jj + kk*width];    /* 補間に使う画素を4×4行列fY[4][4]に代入 */
				}
			}
			for (loopw = 0; loopw <= 3; loopw++){
				sumR = 0;
				sumG = 0;
				sumB = 0;
				for (loop = 0; loop <= 3; loop++){
					sumR = sumR + hy[loop] * fR[loopw][loop];
					sumG = sumG + hy[loop] * fG[loopw][loop];
					sumB = sumB + hy[loop] * fB[loopw][loop];
				}
				workR[loopw] = sumR;
				workG[loopw] = sumG;
				workB[loopw] = sumB;
			}
			sumR = 0;
			for (loop = 0; loop <= 3; loop++){
				sumR = sumR + workR[loop] * hx[loop];
				sumG = sumG + workG[loop] * hx[loop];
				sumB = sumB + workB[loop] * hx[loop];
			}
			img_rgb->R[j + k*width] = RoundingInt(sumR);
			img_rgb->G[j + k*width] = RoundingInt(sumG);
			img_rgb->B[j + k*width] = RoundingInt(sumB);
		}
	}

    CopyRGB(img_in, img_rgb);
    Free(img_rgb);
}
