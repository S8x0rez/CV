#ifndef IMGIO_HPP
#define IMGIO_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "data.hpp"

using namespace std;

void ReadBMP(IMG_RGB*, char*);
void ReadYUV(IMG_YUV*, char*, int, int, int);

void WriteBMP(char*, IMG_RGB*);
void WriteYUV(char*, IMG_YUV*);

#endif // IMGIO_HPP
