#include <iostream>
#include <string>
#include <cmath>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    string Cell0DsFilePath = "./Cell0Ds.csv";
    string Cell1DsFilePath = "./Cell1Ds.csv";
    string Cell2DsFilePath = "./Cell2Ds.csv";

    if(!ImportMesh(mesh, Cell0DsFilePath, Cell1DsFilePath, Cell2DsFilePath)){
        cerr << "Something went wrong :( " << endl;
        return -1;
    }

    Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates,
                           {},
                           mesh.Cell0DsMarkers);

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema,
                             {},
                             {},
                             mesh.Cell1DsMarkers);
    


    /* Testing what we found and saved */

    // Testing how the markers were stored
    if(!Cell0DsMarkersAreCorrect(mesh)){
        return 1;
    }
    cout << endl;
    cout << "All the markers for the cells of dimension 0 were correctly stored. Well done ;)" << endl;
    cout << endl;

    if(!Cell1DsMarkersAreCorrect(mesh)){
        return 2;
    }
    cout << "All the markers for the cells of dimension 1 were all correctly stored. Well done ;)" << endl;
    cout << endl;
   
    if(!Cell2DsMarkersAreCorrect(mesh)){
        return 3;
    }
    cout << "All the markers for the cells of dimension 2 were correctly stored. Well done ;)" << endl;
    cout << endl;

    double tolerance = 1e-6;
    // Testing the length of the edges
    if(!EdgesLengthsAreGreaterThanTolerance(mesh, tolerance)){
        return 4;
    }
    cout << "All the edges are real edges, that is they have length greater than 0. Well done ;)" << endl;
    cout << endl;

    // Testing the area of polygons
    if (!PolygonsAreasAreGreaterThanToleranceSquared(mesh, tolerance)){
        return 5;
    }
    cout << "All the polygons have real areas, that is they have an area greater than 0. Well done ;)" << endl;
    cout << endl;


    /* The meshes were exported to ParaView in order to check them. It showed the exact same images that were shared in the folder
    called PolygonalMesh: I uploaded on GitHub the screenshot of ParaView. */

    return 0;
}
