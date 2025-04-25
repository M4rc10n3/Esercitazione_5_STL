#include <iostream>
#include <string>
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
    
    /* Per i marker basta guardare se la stampa dà ciò che ci serve */
    /* Creare delle funzioni per calcolare delle lunghezze e delle aree per effettuare gli altri test */
    /* Per ultimo test usare le funzioni del prof. Vicini o usare le MeshConverter online, creare un 
    file .vtu con il file di output del programma e metterlo in ParaView Glance */
    return 0;
}
