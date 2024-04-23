#include "yuvio.hpp"

void AllocImgYUV(IMG_YUV* img, int width, int height, int color_format) {
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->color_format = color_format;
    
    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

    if (img->color_format == 444) {
        img->Y = MemoryAlloc<uchar>(img->pixel);
        img->U = MemoryAlloc<uchar>(img->pixel);
        img->V = MemoryAlloc<uchar>(img->pixel);
    }
    else {

    }
}
