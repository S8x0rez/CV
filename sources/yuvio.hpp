#ifndef YUVIO_HPP
#define YUVIO_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "data.hpp"

using namespace std;

void AllocImgYUV(IMG_YUV*, int, int);
void Free(IMG_YUV*);
void ReadYUV(IMG_YUV*, char*);
void WriteYUV(char*, IMG_YUV);

#endif // YUVIO?HPP
