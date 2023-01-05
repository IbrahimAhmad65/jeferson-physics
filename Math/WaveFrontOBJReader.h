//
// Created by ibrahim on 1/4/23.
//

#ifndef PHYS2_WAVEFRONTOBJREADER_H
#define PHYS2_WAVEFRONTOBJREADER_H


#include "Mesh.h"

class WaveFrontOBJReader {
public:
    Mesh read( const char * filename);
};


#endif //PHYS2_WAVEFRONTOBJREADER_H
