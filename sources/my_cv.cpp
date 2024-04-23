#include "my_cv.hpp"

void GrayScale(IMG_RGB* img_out, IMG_RGB* img_in)
{
    int width, height;
    uchar value;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){

            // BT.709
            value = RoundingDecimal(0.2126 * (double)img_in->R[j + k * width] + 0.7152 * (double)img_in->G[j + k * width] + 0.0722 * (double)img_in->B[j + k * width]);

            // BT.601
            // value = (0.2990 * (double)img_in->R[j + k * width] + 0.587 * (double)img_in->G[j + k * width] + 0.114 * (double)img_in->B[j + k * width]);

            img_out->R[j + k * width] = value;
            img_out->G[j + k * width] = value;
            img_out->B[j + k * width] = value;
        }
    }
}

void ValueScaling(IMG_RGB* img_out, IMG_RGB* img_in, int a, int b)
{
    int width, height;
    int x;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img_in->R[j + k * width];
            img_out->R[j + k * width] = RoundingInt(a * x + b);

            x = img_in->G[j + k * width];
            img_out->G[j + k * width] = RoundingInt(a * x + b);

            x = img_in->B[j + k * width];
            img_out->B[j + k * width] = RoundingInt(a * x + b);
        }
    }
}

void GammaCorrection(IMG_RGB* img_out, IMG_RGB* img_in, double gamma)
{
    int width, height;
    double x;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img_in->R[j + k * width];
            img_out->R[j + k * width] = RoundingDecimal((x / 255, gamma) * 255);
            x = img_in->G[j + k * width];
            img_out->G[j + k * width] = RoundingDecimal(pow(x / 255, gamma) * 255);
            x = img_in->B[j + k * width];
            img_out->B[j + k * width] = RoundingDecimal(pow(x / 255, gamma) * 255);
        }
    }
}

void SToneCurve(IMG_RGB* img_out, IMG_RGB* img_in, double p)
{
    int width, height;
    double x;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = (double)img_in->R[j + k * width];
            img_out->R[j + k * width] = RoundingDecimal(255 / (1 + exp(p * (-x + 128))));

            x = (double)img_in->G[j + k * width];
            img_out->G[j + k * width] = RoundingDecimal(255 / (1 + exp(p * (-x + 128))));

            x = (double)img_in->B[j + k * width];
            img_out->B[j + k * width] = RoundingDecimal(255 / (1 + exp(p * (-x + 128))));
        }
    }
}

void HighContrast(IMG_RGB* img_out, IMG_RGB* img_in, double a, double b)
{
    if (a >= b) {
        cout << "HighContrast: wrong range (b <= a)" << endl;
        return;
    }

    int width, height;
    double x;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = (double)img_in->R[j + k * width];
            img_out->R[j + k * width] = RoundingDecimal(255 * (x - a) / (b - a));

            x = (double)img_in->G[j + k * width];
            img_out->G[j + k * width] = RoundingDecimal(255 * (x - a) / (b - a));

            x = (double)img_in->B[j + k * width];
            img_out->B[j + k * width] = RoundingDecimal(255 * (x - a) / (b - a));
        }
    }
}

void LowContrast(IMG_RGB* img_out, IMG_RGB* img_in, double a, double b)
{
    if (a >= b) {
        cout << "LowContrast: wrong range (b <= a)" << endl;
        return;
    }

    int width, height;
    double x;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            x = img_in->R[j + k * width];
            img_out->R[j + k * width] = RoundingDecimal((b - a) / 255 * x + a);

            x = img_in->G[j + k * width];
            img_out->G[j + k * width] = RoundingDecimal((b - a) / 255 * x + a);

            x = img_in->B[j + k * width];
            img_out->B[j + k * width] = RoundingDecimal((b - a) / 255 * x + a);
        }
    }
}

void NegaPosiReversal(IMG_RGB* img_out, IMG_RGB* img_in)
{
    int width, height;
    uchar value;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            img_out->R[j + k * width] = 255 - img_in->R[j + k * width];
            img_out->G[j + k * width] = 255 - img_in->G[j + k * width];
            img_out->B[j + k * width] = 255 - img_in->B[j + k * width];
        }
    }

}

void Postarization(IMG_RGB* img_out, IMG_RGB* img_in, int lv)
{
    int width, height;
    uchar value;
    int band;

    width = img_in->width;
    height = img_in->height;
    band = 255 / lv;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            img_out->R[j + k * width] = img_in->R[j + k * width] / band * band;
            img_out->G[j + k * width] = img_in->G[j + k * width] / band * band;
            img_out->B[j + k * width] = img_in->B[j + k * width] / band * band;
        }
    }
}

void Solarization(IMG_RGB* img_out, IMG_RGB* img_in, int a)
{
    int width, height;
    int value;
    int flag = 255 / a;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            value = img_in->R[j + k * width];
            if ((value / flag) % 2) img_out->R[j + k * width] = RoundingInt(255 - value * a - 255 * (value / flag));
            else img_out->R[j + k * width] = RoundingInt(value * a - 255 * (value / flag));
        }
    }
}


void Binarize(IMG_RGB* img_out, IMG_RGB* img_in, int threshold)
{
    int width, height;
    uchar value;

    width = img_in->width;
    height = img_in->height;

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            if (img_in->R[j + k * width] >= threshold) {
                img_out->R[j + k * width] = 255;
                img_out->G[j + k * width] = 255;
                img_out->B[j + k * width] = 255;
            }
            else {
                img_out->R[j + k * width] = 0;
                img_out->G[j + k * width] = 0;
                img_out->B[j + k * width] = 0;
            }
        }
    }
}

void PrewittFilter(IMG_RGB* img_out, IMG_RGB* img_in, int mode, int d)  // in: gray scale
{
    int width, height;
    int value;

    width = img_in->width;
    height = img_in->height;


    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            value = 0;
            if (mode != 1) {    // Vertical edge ditection
                value += -1 * img_in->R[(j - 1) + (k - 1) * width] + 1 * img_in->R[(j + 1) + (k - 1) * width]
                         -1 * img_in->R[(j - 1) + k * width]       + 1 * img_in->R[(j + 1) + k * width]
                         -1 * img_in->R[(j - 1) + (k + 1) * width] + 1 * img_in->R[(j + 1) + (k + 1) * width];
            }
            if (mode !=2) {    // Horisontal edge ditection
                value += -1 * img_in->R[(j - 1) + (k - 1) * width] -2 * img_in->R[j + (k - 1) * width] -1 * img_in->R[(j + 1) + (k - 1) * width]
                         +1 * img_in->R[(j - 1) + (k + 1) * width] +2 * img_in->R[j + (k + 1) * width] +1 * img_in->R[(j + 1) + (k + 1) * width];
            }
            img_out->R[j + k * width] = RoundingInt(d * value);
            img_out->G[j + k * width] = RoundingInt(d * value);
            img_out->B[j + k * width] = RoundingInt(d * value);
        }
    }
}

void SobelFilter(IMG_RGB* img_out, IMG_RGB* img_in, int mode, int d)  // in: gray scale
{
    int width, height;
    int value;

    width = img_in->width;
    height = img_in->height;


    for (int k = 1; k < height - 1; k++){
        for (int j = 1; j < width - 1; j++){
            value = 0;
            if (mode != 1) {    // Vertical edge ditection
                value += -1 * img_in->R[(j - 1) + (k - 1) * width] + 1 * img_in->R[(j + 1) + (k - 1) * width]
                         -2 * img_in->R[(j - 1) + k * width]       + 2 * img_in->R[(j + 1) + k * width]
                         -1 * img_in->R[(j - 1) + (k + 1) * width] + 1 * img_in->R[(j + 1) + (k + 1) * width];
            }
            if (mode !=2) {    // Horisontal edge ditection
                value += -1 * img_in->R[(j - 1) + (k - 1) * width] -2 * img_in->R[j + (k - 1) * width] -1 * img_in->R[(j + 1) + (k - 1) * width]
                         +1 * img_in->R[(j - 1) + (k + 1) * width] +2 * img_in->R[j + (k + 1) * width] +1 * img_in->R[(j + 1) + (k + 1) * width];
            }
            img_out->R[j + k * width] = RoundingInt(d * value);
            img_out->G[j + k * width] = RoundingInt(d * value);
            img_out->B[j + k * width] = RoundingInt(d * value);
        }
    }
}

void LaplacianFilter(IMG_RGB* img_out, IMG_RGB* img_in, int direction, int d)  // in: gray scale
{
    int width, height;

    width = img_in->width;
    height = img_in->height;

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
            img_out->R[j + k * width] = RoundingInt(d * value[0]);
            img_out->G[j + k * width] = RoundingInt(d * value[1]);
            img_out->B[j + k * width] = RoundingInt(d * value[2]);
        }
    }
}

void MeanFilter(IMG_RGB* img_out, IMG_RGB* img_in, int size)
{
    if (size % 2 == 0) {
        cout << "MeanFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "MeanFilter: filter size error (size is even number)" << endl;
        return;
    }

    int width, height;
    int r;

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

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
            img_out->R[j + k * width] = RoundingInt(value[0] / size);
            img_out->G[j + k * width] = RoundingInt(value[1] / size);
            img_out->B[j + k * width] = RoundingInt(value[2] / size);
        }
    }
}

void WeightedMeanFilter(IMG_RGB* img_out, IMG_RGB* img_in, int add)
{
    int width, height;
    int value[3];

    width = img_in->width;
    height = img_in->height;

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

            img_out->R[j + k * width] = RoundingInt(value[0] / (9 + add));
            img_out->G[j + k * width] = RoundingInt(value[1] / (9 + add));
            img_out->B[j + k * width] = RoundingInt(value[2] / (9 + add));
        }
    }
}

void MedialFilter(IMG_RGB* img_out, IMG_RGB* img_in, int size)
{
    if (size % 2 == 0) {
        cout << "MedianFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "MedianFilter: filter size error (size is even number)" << endl;
        return;
    }

    int width, height;
    int r, median;

    int** array = new int*[3];
    for (int i = 0; i < 3; i++) {
        array[i] = new int[size * size];
    }

    width = img_in->width;
    height = img_in->height;
    r = size / 2;
    median = size * size / 2 + 1;

    for (int k = r; k < height - r; k++){
        for (int j = r; j < width - r; j++){
            for (int kk = -r; kk <= r; kk++) {
                for (int jj = -r; jj <= r; jj++) {
                    array[0][(jj + r) + (kk + r) * size] += img_in->R[(j + jj) + (k + kk) * width];
                    array[1][(jj + r) + (kk + r) * size] += img_in->G[(j + jj) + (k + kk) * width];
                    array[2][(jj + r) + (kk + r) * size] += img_in->B[(j + jj) + (k + kk) * width];
                }
            }

            sort(array[0], array[0] + size * size);
            sort(array[1], array[1] + size * size);
            sort(array[2], array[2] + size * size);
            img_out->R[j + k * width] = array[0][median];
            img_out->G[j + k * width] = array[1][median];
            img_out->B[j + k * width] = array[2][median];
        }
    }

    for (int i = 0; i < 3; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void GaussianFilter(IMG_RGB* img_out, IMG_RGB* img_in, int size, double sigma)
{
    if (size % 2 == 0) {
        cout << "GaussianFilter: filter size error (size is even number)" << endl;
        return;
    }
    else if (img_in->width < size || img_in->height < size) {
        cout << "GaussianFilter: filter size error (size is even number)" << endl;
        return;
    }

    int width, height;
    int r;
    double* array = new double[size * size];

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

    for (int k = -r; k <= r; k++) {
        for (int j = -r; j <= r; j++) {
            array[(j + r) + (k + r) * size] = exp(-((k << 2) +(j << 2)) / (2 * pow(sigma, 2.))) / (2 * PI * pow(sigma, 2.));
        }
    }

    for (int k = r; k < height - r; k++) {
        for (int j = r; j < width - r; j++) {
            double value[3] = {0, 0, 0};
            for (int kk = -r; kk <= r; kk++) {
                for (int jj = -r; jj <= r; jj++) {
                    value[0] += img_in->R[(j + jj) + (k + kk) * width] * array[(j + r) + (k + r) * size];
                    value[1] += img_in->G[(j + jj) + (k + kk) * width] * array[(j + r) + (k + r) * size];
                    value[2] += img_in->B[(j + jj) + (k + kk) * width] * array[(j + r) + (k + r) * size];
                }
            }

            img_out->R[j + k * width] = value[0];
            img_out->G[j + k * width] = value[1];
            img_out->B[j + k * width] = value[2];
        }
    }

    delete[] array;
}

void MotionBlur(IMG_RGB* img_out, IMG_RGB* img_in, int size, int direction)
{
    int width, height;
    int r;

    width = img_in->width;
    height = img_in->height;
    r = size / 2;

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

                img_out->R[j + k * width] = RoundingInt(value[0] / (size << 2));
                img_out->G[j + k * width] = RoundingInt(value[1] / (size << 2));
                img_out->B[j + k * width] = RoundingInt(value[2] / (size << 2));
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

                img_out->R[j + k * width] = RoundingInt(value[0] / size);
                img_out->G[j + k * width] = RoundingInt(value[1] / size);
                img_out->B[j + k * width] = RoundingInt(value[2] / size);
            }
            }
    }
}
