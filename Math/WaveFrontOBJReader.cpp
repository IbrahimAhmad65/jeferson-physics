//
// Created by ibrahim on 1/4/23.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include "WaveFrontOBJReader.h"
#include <vector>
#include "Triangle.h"


Mesh WaveFrontOBJReader::read(const char *filename) {
    std::vector<Vector3D> vertices;
    std::vector<int> faceIndex;
    std::ifstream in(filename, std::ios::in);
    if (!in) {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);

    }
    bool o = false;
    std::string line;
    while (std::getline(in, line)) {
        //check v for vertices

        if (line.substr(0, 2) == "v ") {
            std::istringstream v(line.substr(2));
            Vector3D vert;
            double x, y, z;
            v >> x;
            v >> y;
            v >> z;
            vert = Vector3D(x, y, z);
            vertices.push_back(vert);
        }
            //check for texture co-ordinate

            //check for faces
        else if (line.substr(0, 2) == "f ") {
            int a, b, c; //to store mesh index
            int garbo;
            //std::istringstream v;
            //v.str(line.substr(2));
            const char *chh = line.c_str();
            sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &garbo, &garbo, &b, &garbo, &garbo, &c, &garbo,& garbo); //here it read the line start with f and store the corresponding values in the variables

            //v>>a;v>>b;v>>c;
            a--;
            b--;
            c--;
            faceIndex.push_back(a);
            faceIndex.push_back(b);
            faceIndex.push_back(c);
        }else if(line.substr(0, 2) == "o "){
            if(!o){
                o = true;
            }else{
                break;
            }
        }

    }
//the mesh data is finally calculated here
    auto* triangle = new Triangle[faceIndex.size()/3];
    for (unsigned int i = 0; i < faceIndex.size(); i+=3) {
        Vector3D vert1, vert2, vert3;
        vert1 = Vector3D(vertices[faceIndex[i]].getI(), vertices[faceIndex[i]].getJ(),
                            vertices[faceIndex[i]].getK());
        vert2 = Vector3D(vertices[faceIndex[i+1]].getI(), vertices[faceIndex[i+1]].getJ(),
                         vertices[faceIndex[i+1]].getK());
        vert3 = Vector3D(vertices[faceIndex[i+2]].getI(), vertices[faceIndex[i+2]].getJ(),
                         vertices[faceIndex[i+2]].getK());
        triangle[i/3] = Triangle(vert1.clone(),vert2.clone(),vert3.clone());
    }
    return {triangle, 3, static_cast<int>(faceIndex.size())/3,-1};
}
