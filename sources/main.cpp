#include <iostream>
#include <cstring>

#include "my_cv.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    char infname[512];
    char outfname[512];

    IMG_RGB* img = new IMG_RGB;

    if(argc < 3){
        cerr << "Usage: " << argv[0] << " infname outfname color_space color_format" << endl;
        cout << "        infname: input file name (bitmap)" << endl;
        cout << "        outfname: output file name (bitmap)" << endl;
        exit(-1);
    }

    strncpy(infname, argv[1], 512);
    strncpy(outfname, argv[2], 512);

    cout << " - Input parameters --------" << endl;
    cout << "   -- input file= " << infname << endl;
    cout << "   -- output file= " << outfname << endl;
    
    ReadBMP(img, infname);
    WriteBMP(outfname, img);
    Free(img);

    return 0;
}