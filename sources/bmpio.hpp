#ifndef BMPIO_HPP
#define BMPIO_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "data.hpp"

using namespace std;

void AllocImgRGB(IMG_RGB*, int, int);
void Free(IMG_RGB*);
void ReadBMP(IMG_RGB*, char*);
void WriteBMP(char*, IMG_RGB*);

#endif // BMPIO_HPP
