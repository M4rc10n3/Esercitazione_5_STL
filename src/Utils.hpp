#pragma once

#include <string>
#include "PolygonalMesh.hpp"

namespace PolygonalLibrary{

    /* ImportMesh imports the data inside the object mesh of type PolygonalMesh.

    mesh: the object in which it stores the data;
    Cell0DsFilePath: the string that is the path to the file containing the data for the cells of dimension 0;
    Cell1DsFilePath: the string that is the path to the file containing the data for the cells of dimension 1;
    Cell2DsFilePath: the string that is the path to the file containing the data for the cells of dimension 2 */
    bool ImportMesh(PolygonalMesh& mesh, 
        const string& Cell0DsFilePath = {},
        const string& Cell1DsFilePath = {},
        const string& Cell2DsFilePath = {});


    /* ImportCell0Ds imports the data of the cells of dimension 0 inside the object mesh of type PolygonalMesh. 

    mesh: the object in which it stores the data;
    filePath: the string that is the path to the file containing the data for the cells of dimension 0 */
    bool ImportCell0Ds(const string& filePath, PolygonalMesh& mesh);

    /* ImportCell1Ds imports the data of the cells of dimension 1 inside the object mesh of type PolygonalMesh.

    mesh: the object in which it stores the data;
    filePath: the string that is the path to the file containing the data for the cells of dimension 1 */
    bool ImportCell1Ds(const string& filePath, PolygonalMesh& mesh);

    /* ImportCell2Ds imports the data of the cells of dimension 2 inside the object mesh of type PolygonalMesh .

    mesh: the object in which it stores the data;
    filePath: the string that is the path to the file containing the data for the cells of dimension 2 */
    bool ImportCell2Ds(const string& filePath, PolygonalMesh& mesh);


    /* Cell0DsMarkersAreCorrect is a testing function that checks if the markers of the cells of dimension 0 were correctly stored.
    
    mesh: the object in which the data is stored;*/
    bool Cell0DsMarkersAreCorrect(PolygonalMesh& mesh);


    /* Cell1DsMarkersAreCorrect is a testing function that checks if the markers of the cells of dimension 1 were correctly stored.
    
    mesh: the object in which the data is stored */
    bool Cell1DsMarkersAreCorrect(PolygonalMesh& mesh);


    /* Cell2DsMarkersAreCorrect is a testing function that checks if the markers of the cells of dimension 2 were correctly stored.
    
    mesh: the object in which the data is stored */
    bool Cell2DsMarkersAreCorrect(PolygonalMesh& mesh);

    
    /* EdgesLengthsAreGreaterThanZero is a testing function that checks whether every edge stored in the object mesh 
    of type PolygonalMesh is a proper edge, that is it has a length greater than tolerance.
    
    mesh: the object in which the data is stored;
    tolerance: what the length of each edge should be greater of */
    bool EdgesLengthsAreGreaterThanZero(PolygonalMesh& mesh, const double& tolerance);
    

    /* PolygonsAreasAreGreaterThanZero is a testing function that checks whether every polygon stored in the object mesh 
    of type PolygonalMesh has got a proper area, that is it has an area greater than tolerance squared. 

    mesh: the object in which the data is stored;
    tolerance: what the square root of the area of each polygon should be greater of */
    bool PolygonsAreasAreGreaterThanZero(PolygonalMesh& mesh, const double& tolerance);

}

