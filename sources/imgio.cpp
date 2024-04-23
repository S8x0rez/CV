#include "imgio.hpp"

void AllocImg(IMG_COMMON* img, int width, int height, int channel)
{
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->channel = channel;

    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

    // img->value = MemoryAlloc<uchar>(img->pixel * img->channel);
}

void Free(IMG_COMMON* img)
{
    delete[] img->value;
    delete img;
}
