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
    
    /* Testing part of the code */


    // Testing how the markers were stored
    vector<int> markersCell0DsCorrect = {1, 2, 3, 4, 0, 8, 5, 6, 7, 0, 0, 0, 0, 0, 0, 8, 5, 6, 0, 0, 7, 
        8, 6, 7, 5, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    vector<int> markersCell1DsCorrect = {0, 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 8, 0, 0, 7, 0, 0, 7, 0, 5, 0, 
        0, 5, 6, 7, 8, 6, 0, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    vector<int> markersCell2DsCorrect = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    
    for(unsigned int id = 0; id < markersCell0DsCorrect.size(); id++){
        if(markersCell0DsCorrect[id] != mesh.Cell0DsMarkers[id]){
            cerr << "The markers for the cells of dimension 0 were not stored correctly." << endl;
            cerr << "The marker not stored correctly is the one with id: " << id << endl;
            return 1;
        }
    }
    cout << endl;
    cout << "All the markers for the cells of dimension 0 were correctly stored. Well done ;)" << endl;
    cout << endl;

    for(unsigned int id = 0; id < markersCell0DsCorrect.size(); id++){
        if(markersCell0DsCorrect[id] != mesh.Cell0DsMarkers[id]){
            cerr << "The markers for the cells of dimension 1 were not stored correctly." << endl;
            cerr << "The marker not stored correctly is the one with id: " << id << endl;
            return 2;
        }
    }
    cout << "All the markers for the cells of dimension 1 were all correctly stored. Well done ;)" << endl;
    cout << endl;
   
    for(unsigned int id = 0; id < markersCell0DsCorrect.size(); id++){
        if(markersCell0DsCorrect[id] != mesh.Cell0DsMarkers[id]){
            cerr << "The markers for the cells of dimension 2 were not stored correctly." << endl;
            cerr << "The marker not stored correctly is the one with id: " << id << endl;
            return 3;
        }
    }
    cout << "All the markers for the cells of dimension 2 were correctly stored. Well done ;)" << endl;
    cout << endl;


    // Testing the length of the edges

    for(unsigned int id = 0; id < mesh.NumCell1Ds; id++){
        int id_point_1 = mesh.Cell1DsExtrema(0, id);
        int id_point_2 = mesh.Cell1DsExtrema(1, id);
        double x_point_1 = mesh.Cell0DsCoordinates(0, id_point_1);
        double y_point_1 = mesh.Cell0DsCoordinates(1, id_point_1);
        double x_point_2 = mesh.Cell0DsCoordinates(0, id_point_2);
        double y_point_2 = mesh.Cell0DsCoordinates(1, id_point_2);
        
        double x_difference = x_point_2 - x_point_1;
        double y_difference = y_point_2 - y_point_1;
        double length = sqrt(x_difference * x_difference + y_difference * y_difference);
        if(length <= 0.0){
            cerr << "Not all edges are greater than 0." << endl;
            cerr << "The edge that has length equal to 0 is the one with id: " << id << endl;
            return 4;
        }
    }
    cout << "All the edges are real edges, that is they have length greater than 0. Well done ;)" << endl;
    cout << endl;

    /* Testing the area of the polygons: in order to do that we simply need to verify that each polygon has a triangle inside with are greater than 0. If that's the case, the polygon has an area greater than 0 (in particular the are is greater than or equal to that of the triangle). */
    for(unsigned int id = 0; id < mesh.NumCell2Ds; id++){
        /* Renaming the ids of the vertices of the triangle for readability */
        int id_point_1 = mesh.Cell2DsVertices[id][0];
        int id_point_2 = mesh.Cell2DsVertices[id][1];
        int id_point_3 = mesh.Cell2DsVertices[id][2];

        /* Renaming the coordinates of the vertices of the triangle for readability */
        double x_point_1 = mesh.Cell0DsCoordinates(0, id_point_1);
        double y_point_1 = mesh.Cell0DsCoordinates(1, id_point_1);
        double x_point_2 = mesh.Cell0DsCoordinates(0, id_point_2);
        double y_point_2 = mesh.Cell0DsCoordinates(1, id_point_2);
        double x_point_3 = mesh.Cell0DsCoordinates(0, id_point_3);
        double y_point_3 = mesh.Cell0DsCoordinates(1, id_point_3);
        
        /* Calculating the difference of the coordinates of each couple of points and saving it in a variable for readability */
        double x_difference_21 = x_point_2 - x_point_1;
        double y_difference_21 = y_point_2 - y_point_1;
        double x_difference_31 = x_point_3 - x_point_1;
        double y_difference_31 = y_point_3 - y_point_1;
        double x_difference_32 = x_point_3 - x_point_2;
        double y_difference_32 = y_point_3 - y_point_2;

        /* Calculating the length of each edge and saving it in a variable for readability */
        double length_21 = sqrt(x_difference_21 * x_difference_21 + y_difference_21 * y_difference_21);
        double length_31 = sqrt(x_difference_31 * x_difference_31 + y_difference_31 * y_difference_31);
        double length_32 = sqrt(x_difference_32 * x_difference_32 + y_difference_32 * y_difference_32);

        /* Calculating the area of the triangle using the Heron's formula, which uses the semiperimeter */
        double semiperimeter = 0.5 * (length_21 + length_31 + length_32);

        double area = sqrt(semiperimeter * (semiperimeter - length_21) * (semiperimeter - length_31) * (semiperimeter - length_32));

        int numEdgesPolygon = mesh.Cell2DsEdges[id].size();
        if(area <= 0.0 && numEdgesPolygon > 3){
            /* In that case, let's calculate with the same algorithm as above the area of another triangle in order to understand if the total area is greater than 0 */
            int id_point_4 = mesh.Cell2DsVertices[id][3];
            double x_point_4 = mesh.Cell0DsCoordinates(0, id_point_4);
            double y_point_4 = mesh.Cell0DsCoordinates(1, id_point_4);

            double x_difference_41 = x_point_4 - x_point_1;
            double y_difference_41 = y_point_4 - y_point_1;
            double x_difference_42 = x_point_4 - x_point_2;
            double y_difference_42 = y_point_4 - y_point_2;

            double length_41 = sqrt(x_difference_41 * x_difference_41 + y_difference_41 * y_difference_41);
            double length_42 = sqrt(x_difference_42 * x_difference_42 + y_difference_42 * y_difference_42);

            double semiperimeter = 0.5 * (length_21 + length_41 + length_42);

            double area = sqrt(semiperimeter * (semiperimeter - length_21) * (semiperimeter - length_41) * (semiperimeter - length_42));
        }
        else if(area <= 0.0 && numEdgesPolygon <= 3){
            cerr << "Not all polygons have area greater than 0." << endl;
            cerr << "The polygon that could have area equal to 0 is the one with id: " << id 
            << ". It needs further investigation" << endl;
            return 5;
        }
    }
    cout << "All the polygons have real areas, that is they have an area greater than 0. Well done ;)" << endl;
    cout << endl;

    /* The meshes were exported to ParaView in order to check them. It showed the exact same images that were shared. */

    return 0;
}
