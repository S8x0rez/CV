<<<<<<<< HEAD:src/imgio.cpp
#include "imgio.hpp"

//------------------------------------------------------
// Function-ID: 
// Function-Name: 
// Abstract: 
// Argument: 
// Return-Value: 
// Special_Desc:
//------------------------------------------------------
void ReadBMP(IMG_RGB* img, char* filename)
{
    ifstream ifs(filename, ios::binary);
    if (ifs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    int head[54];
    for (int c = 0; c < 54; c++)  {
        head[c] = ifs.get();
    }

    int width = head[18] | head[19] << 8 | head[20] << 16 | head[21] << 24;
	int height = head[22] | head[23] << 8 | head[24] << 16 | head[25] << 24;
    int bit_count = head[28] | head[29] << 8;

    AllocImgRGB(img, width, height);

    cout << "Image size : width =" << img->width << "  height =" << img->height << endl;
    cout << "Image bit count =" << bit_count << endl;

    for (int k = img->height - 1; k >= 0; k--) {
        for (int j = 0; j < img->width; j++) {
            img->B[j + k * img->width] = ifs.get();
            img->G[j + k * img->width] = ifs.get();
            img->R[j + k * img->width] = ifs.get();
        }
    }

    ifs.close();
}

void ReadYUV(IMG_YUV* img, char* filename, int width, int height, int color_format)
{
    ifstream ifs(filename, ios::binary);
    if (ifs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    AllocImgYUV(img, width, height, color_format);

    cout << "Image size : width =" << img->width << "  height =" << img->height << endl;
    cout << "Image color format =" << color_format << endl;

    if (color_format == 422) {

    }
    else if (color_format == 420) {

    }
    else {  // color_format == 444
        for (int k = 0; k < img->height; k++) {
            for (int j = 0; j < img->width; j++) {
                img->Y[j + k * width] = ifs.get();
                img->U[j + k * width] = ifs.get();
                img->V[j + k * width] = ifs.get();
            }
        }
    }

    ifs.close();
}

void WriteBMP(char* filename, IMG_RGB* img)
{
    ofstream ofs(filename, ios::binary);
    if (ofs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    int width, height;
    int size;

    width = img->width;
    height = img->height;
    size = width * height;
    
    uchar header_buf[54];
    unsigned int file_size;
    unsigned int offset_to_data;
    unsigned long info_header_size;
    unsigned int planes;
    unsigned int color;
    unsigned long compress;
    unsigned long data_size;
    long xppm;
    long yppm;

    file_size = size * 3 + 54;
    offset_to_data = 54;
    info_header_size = 40;
    planes = 1;
    color = 24;
    compress = 0;
    data_size = size;
    xppm = 1;
    yppm = 1;

    header_buf[0] = 'B';
    header_buf[1] = 'M';
    memcpy(header_buf + 2, &file_size, sizeof(file_size));
    header_buf[6] = 0;
    header_buf[7] = 0;
    header_buf[8] = 0;
    header_buf[9] = 0;
    memcpy(header_buf + 10, &offset_to_data, sizeof(offset_to_data));
    memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
    header_buf[15] = 0;
    header_buf[16] = 0;
    header_buf[17] = 0;
    memcpy(header_buf + 18, &width, sizeof(width));
    memcpy(header_buf + 22, &height, sizeof(height));
    memcpy(header_buf + 26, &planes, sizeof(planes));
    memcpy(header_buf + 28, &color, sizeof(color));
    memcpy(header_buf + 30, &compress, sizeof(compress));
    memcpy(header_buf + 34, &data_size, sizeof(data_size));
    memcpy(header_buf + 38, &xppm, sizeof(xppm));
    memcpy(header_buf + 42, &yppm, sizeof(yppm));
    header_buf[46] = 0;
    header_buf[47] = 0;
    header_buf[48] = 0;
    header_buf[49] = 0;
    header_buf[50] = 0;
    header_buf[51] = 0;
    header_buf[52] = 0;
    header_buf[53] = 0;

    ofs.write((char*)header_buf, 54);
    for (int k = height - 1; k >= 0; k--) {
        for (int j = 0; j < width; j++) {
            ofs << img->B[j + k * width];
            ofs << img->G[j + k * width];
            ofs << img->R[j + k * width];
        }
    }
    
    ofs.close();
}

void WriteYUV(char* filename, IMG_YUV* img)
{
    ofstream ofs(filename, ios::binary);
    if (ofs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    if (img->color_format == 422) {

    }
    else if (img->color_format == 420) {

    }
    else {  // color_format == 444
        for (int k = 0; k < img->height; k++) {
            for (int j = 0; j < img->width; j++) {
                ofs << img->Y[j + k * img->width];
                ofs << img->U[j + k * img->width];
                ofs << img->V[j + k * img->width];
            }
        }
    }

    ofs.close();
}
========
#include "imgio.hpp"

//------------------------------------------------------
// Function-ID: 
// Function-Name: 
// Abstract: 
// Argument: 
// Return-Value: 
// Special_Desc:
//------------------------------------------------------
void ReadBMP(IMG_RGB* img, char* filename)
{
    ifstream ifs(filename, ios::binary);
    if (ifs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    int head[54];
    for (int c = 0; c < 54; c++)  {
        head[c] = ifs.get();
    }

    int width = head[18] | head[19] << 8 | head[20] << 16 | head[21] << 24;
	int height = head[22] | head[23] << 8 | head[24] << 16 | head[25] << 24;
    int bit_count = head[28] | head[29] << 8;

    AllocImgRGB(img, width, height);

    cout << "Image size : width =" << img->width << "  height =" << img->height << endl;
    cout << "Image bit count =" << bit_count << endl;

    for (int k = img->height - 1; k >= 0; k--) {
        for (int j = 0; j < img->width; j++) {
            img->B[j + k * img->width] = ifs.get();
            img->G[j + k * img->width] = ifs.get();
            img->R[j + k * img->width] = ifs.get();
        }
    }

    ifs.close();
}

void ReadYUV(IMG_YUV* img, char* filename, int width, int height, int color_format)
{
    ifstream ifs(filename, ios::binary);
    if (ifs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    AllocImgYUV(img, width, height, color_format);

    cout << "Image size : width =" << img->width << "  height =" << img->height << endl;
    cout << "Image color format =" << color_format << endl;

    if (color_format == 422) {

    }
    else if (color_format == 420) {

    }
    else {  // color_format == 444
        for (int k = 0; k < img->height; k++) {
            for (int j = 0; j < img->width; j++) {
                img->Y[j + k * width] = ifs.get();
                img->U[j + k * width] = ifs.get();
                img->V[j + k * width] = ifs.get();
            }
        }
    }

    ifs.close();
}

void WriteBMP(char* filename, IMG_RGB* img)
{
    ofstream ofs(filename, ios::binary);
    if (ofs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    int width, height;
    int size;

    width = img->width;
    height = img->height;
    size = width * height;
    
    uchar header_buf[54];
    unsigned int file_size;
    unsigned int offset_to_data;
    unsigned long info_header_size;
    unsigned int planes;
    unsigned int color;
    unsigned long compress;
    unsigned long data_size;
    long xppm;
    long yppm;

    file_size = size * 3 + 54;
    offset_to_data = 54;
    info_header_size = 40;
    planes = 1;
    color = 24;
    compress = 0;
    data_size = size;
    xppm = 1;
    yppm = 1;

    header_buf[0] = 'B';
    header_buf[1] = 'M';
    memcpy(header_buf + 2, &file_size, sizeof(file_size));
    header_buf[6] = 0;
    header_buf[7] = 0;
    header_buf[8] = 0;
    header_buf[9] = 0;
    memcpy(header_buf + 10, &offset_to_data, sizeof(offset_to_data));
    memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
    header_buf[15] = 0;
    header_buf[16] = 0;
    header_buf[17] = 0;
    memcpy(header_buf + 18, &width, sizeof(width));
    memcpy(header_buf + 22, &height, sizeof(height));
    memcpy(header_buf + 26, &planes, sizeof(planes));
    memcpy(header_buf + 28, &color, sizeof(color));
    memcpy(header_buf + 30, &compress, sizeof(compress));
    memcpy(header_buf + 34, &data_size, sizeof(data_size));
    memcpy(header_buf + 38, &xppm, sizeof(xppm));
    memcpy(header_buf + 42, &yppm, sizeof(yppm));
    header_buf[46] = 0;
    header_buf[47] = 0;
    header_buf[48] = 0;
    header_buf[49] = 0;
    header_buf[50] = 0;
    header_buf[51] = 0;
    header_buf[52] = 0;
    header_buf[53] = 0;

    ofs.write((char*)header_buf, 54);
    for (int k = height - 1; k >= 0; k--) {
        for (int j = 0; j < width; j++) {
            ofs << img->B[j + k * width];
            ofs << img->G[j + k * width];
            ofs << img->R[j + k * width];
        }
    }
    
    ofs.close();
}

void WriteYUV(char* filename, IMG_YUV* img)
{
    ofstream ofs(filename, ios::binary);
    if (ofs.fail()) {
        cerr << "File open error = " << filename << endl;
        exit(-1);
    }

    if (img->color_format == 422) {

    }
    else if (img->color_format == 420) {

    }
    else {  // color_format == 444
        for (int k = 0; k < img->height; k++) {
            for (int j = 0; j < img->width; j++) {
                ofs << img->Y[j + k * img->width];
                ofs << img->U[j + k * img->width];
                ofs << img->V[j + k * img->width];
            }
        }
    }

    ofs.close();
}
>>>>>>>> 98fe7ed92dd594f465d2926599eeadccf70b21a8:imgio.cpp
