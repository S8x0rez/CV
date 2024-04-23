#ifndef IMGIO_HPP
#define IMGIO_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "data.hpp"

using namespace std;

void AllocImg(IMG_COMMON*, int, int, int);
void Free(IMG_COMMON*);

#endif // IMGIO_HPP
