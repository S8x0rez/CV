#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

#define PI 3.14159265

typedef unsigned char uchar;
using namespace std;

typedef struct _IMG_COMMON {
    int width;
    int height;
    int pixel;
    int channel;
    uchar** value;
} IMG_COMMON;

typedef struct _IMG_RGB {
    int width;
    int height;
    int pixel;
    uchar* R;
    uchar* G;
    uchar* B;
} IMG_RGB;

typedef struct _IMG_HSV {
    int width;
    int height;
    int pixel;
    int* H;
    uchar* S;
    uchar* V;
} IMG_HSV;

typedef struct _IMG_YUV {
    int width;
    int height;
    int pixel;
    int color_format;
    uchar* Y;
    uchar* U;
    uchar* V;
} IMG_YUV;

template <typename T>
T* MemoryAlloc(int size)
{
    T* m;
    if ((m = new T[size]) == NULL) {
        cerr << "MemoryAlloc: memory allocation error." << endl;
        exit(-1);
    }
    return m;
}

void AllocImg(IMG_COMMON*, int, int, int);
void AllocImgRGB(IMG_RGB*, int, int);
void AllocImgHSV(IMG_HSV*, int, int);
void AllocImgYUV(IMG_YUV*, int, int, int);

void Free(IMG_COMMON*);
void Free(IMG_RGB*);
void Free(IMG_HSV*);
void Free(IMG_YUV*);

void CopyIMG(IMG_COMMON*, IMG_COMMON*);
void CopyRGB(IMG_RGB*, IMG_RGB*);
void CopyHSV(IMG_HSV*, IMG_HSV*);
void CopyYUV(IMG_YUV*, IMG_YUV*);

uchar RoundingUC(double);
uchar RoundingUC(int);
int RoundingInt(double);

void YUV2HSV(IMG_HSV*, IMG_YUV*);
void HSV2YUV(IMG_YUV*, IMG_HSV*);
void RGB2HSV(IMG_HSV*, IMG_RGB*);
void HSV2RGB(IMG_RGB*, IMG_HSV*);
void RGB2YUV(IMG_YUV*, IMG_RGB*, int);
void YUV2RGB(IMG_RGB*, IMG_YUV*, int);

#endif // DATA_HPP
