#include <iostream>
#include <string>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "test_PolygonalMesh.hpp"

#include <gtest/gtest.h>

using namespace std;
using namespace PolygonalLibrary;

int main(int argc, char *argv[]){
    PolygonalMesh mesh;

    string Cell0DsFilePath = "./Cell0Ds.csv";
    string Cell1DsFilePath = "./Cell1Ds.csv";
    string Cell2DsFilePath = "./Cell2Ds.csv";

    if(!ImportMesh(mesh, Cell0DsFilePath, Cell1DsFilePath, Cell2DsFilePath)){
        cerr << "Something went wrong :( " << endl;
        return -1;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
