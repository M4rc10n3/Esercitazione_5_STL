#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "Eigen/Core"
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{

    bool ImportMesh(PolygonalMesh& mesh,
        const string& Cell0DsFilePath,
        const string& Cell1DsFilePath,
        const string& Cell2DsFilePath){

        if(!ImportCell0Ds(Cell0DsFilePath, mesh)){
            return false;
        }
        else if(!ImportCell1Ds(Cell1DsFilePath, mesh)){
            return false;
        }
        else if(!ImportCell2Ds(Cell2DsFilePath, mesh)){
            return false;
        }

        return true;
    }

    bool ImportCell0Ds(const string& filePath, PolygonalMesh& mesh){

        ifstream file(filePath);
        if(file.fail()){
            cerr << "Couldn't open file with path: " << filePath << endl;
            return false;
        }

        list<string> listOfAllLines;
        
        string line;
        while(getline(file, line)){
            listOfAllLines.push_back(line);
        }
        file.close(); // optional, not needed
        
        // Let's remove the header of the csv file from the list
        listOfAllLines.pop_front();

        // Let's store all of the list contents inside the appropriate containers
        mesh.NumCell0Ds = listOfAllLines.size();

        if(mesh.NumCell0Ds == 0){
            cerr << "There are no cells 0D." << endl;
            return false;
        }

        // Let's reserve the memory needed to store all of the elements of each container
        mesh.Cell0DsIds.reserve(mesh.NumCell0Ds);
        mesh.Cell0DsCoordinates = Eigen::Matrix3Xd::Zero(3, mesh.NumCell0Ds);
        mesh.Cell0DsMarkers = Eigen::VectorXi::Zero(mesh.NumCell0Ds);

        for(const string& line : listOfAllLines){

            istringstream inputLine(line);

            char useless; // Here we'll store the useless divider ";"
            unsigned int id;

            inputLine >> id >> useless >> 
                         mesh.Cell0DsMarkers(id) >> useless
                         >> mesh.Cell0DsCoordinates(0, id) >> useless
                         >> mesh.Cell0DsCoordinates(1, id);

        }

        return true;
    }

    bool ImportCell1Ds(const string& filePath, PolygonalMesh& mesh){
        
        ifstream file(filePath);

        if(file.fail()){
            cerr << "Couldn't open file with path: " << filePath << endl;
            return false;
        }
        
        list<string> listOfAllLines;
        
        string line;
        while(getline(file, line)){
            listOfAllLines.push_back(line);
        }
        file.close();

        listOfAllLines.pop_front();

        mesh.NumCell1Ds = listOfAllLines.size();

        if(mesh.NumCell1Ds == 0){
            cerr << "There are no cells 1D." << endl;
            return false;
        }

        mesh.Cell1DsIds.reserve(mesh.NumCell1Ds);
        mesh.Cell1DsExtrema = Eigen::Matrix2Xi::Zero(2, mesh.NumCell1Ds);
        mesh.Cell1DsMarkers = Eigen::VectorXi::Zero(mesh.NumCell1Ds);

        for(const string& line : listOfAllLines){

            istringstream inputLine(line);

            char useless;
            unsigned int id;

            inputLine >> id >> useless 
                      >> mesh.Cell1DsMarkers(id) >> useless
                      >> mesh.Cell1DsExtrema(0, id) >> useless >> mesh.Cell1DsExtrema(1, id);

        }

        return true;
    }

    bool ImportCell2Ds(const string& filePath, PolygonalMesh& mesh){
        
        ifstream file(filePath);

        if(file.fail()){
            cerr << "Couldn't open file with path: " << filePath << endl;
            return false;
        }
        
        list<string> listOfAllLines;

        string line;
        while(getline(file, line)){
            listOfAllLines.push_back(line);
        }
        file.close();

        listOfAllLines.pop_front();

        mesh.NumCell2Ds = listOfAllLines.size();

        if(mesh.NumCell2Ds == 0){
            cerr << "There are no cells 2D." << endl;
            return false;
        }

        mesh.Cell2DsIds.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsMarkers = Eigen::VectorXi::Zero(mesh.NumCell2Ds);
        mesh.Cell2DsVertices.resize(mesh.NumCell2Ds);
        
        mesh.Cell2DsEdges.resize(mesh.NumCell2Ds);

        char useless;
        int id;
        int NumVertices;
        int NumEdges;
        for(const string& line : listOfAllLines){

            istringstream inputLine(line);

            inputLine >> id >> useless
                      >> mesh.Cell2DsMarkers(id) >> useless
                      >> NumVertices;
            
            mesh.Cell2DsVertices[id].resize(NumVertices);

            for(int indexVertices = 0; indexVertices < NumVertices; indexVertices++){
                inputLine >> useless >> mesh.Cell2DsVertices[id][indexVertices];
            }

            inputLine >> useless >> NumEdges;
            mesh.Cell2DsEdges[id].resize(NumEdges);

            for(int indexEdges = 0; indexEdges < NumEdges; indexEdges++){
                inputLine >> useless >> mesh.Cell2DsEdges[id][indexEdges];
            }
            
        }

        return true;
    }

    // Testing functions:

    bool Cell0DsMarkersAreCorrect(PolygonalMesh& mesh){
        vector<int> markersCell0DsCorrect = {1, 2, 3, 4, 0, 8, 5, 6, 7, 0, 0, 0, 0, 0, 0, 8, 5, 6, 0, 0, 7, 
            8, 6, 7, 5, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /* Checking each element of the two vectors and comparing them: if something's not equal, the function returns 
        false and stops, printing on the standard output the id of the markerthat  was not stored properly */
        for(unsigned int id = 0; id < markersCell0DsCorrect.size(); id++){
            if(markersCell0DsCorrect[id] != mesh.Cell0DsMarkers[id]){
                cerr << "The markers for the cells of dimension 0 were not stored correctly." << endl;
                cerr << "The marker not stored correctly is the one with id: " << id << endl;
                return false;
            }
        }

        return true;
    }

    bool Cell1DsMarkersAreCorrect(PolygonalMesh& mesh){
        vector<int> markersCell1DsCorrect = {0, 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 8, 0, 0, 7, 0, 0, 7, 0, 5, 0, 
            0, 5, 6, 7, 8, 6, 0, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /* Checking each element of the two vectors and comparing them: if something's not equal, the function returns 
        false and stops, printing on the standard output the id of the markerthat  was not stored properly */
        for(unsigned int id = 0; id < markersCell1DsCorrect.size(); id++){
            if(markersCell1DsCorrect[id] != mesh.Cell1DsMarkers[id]){
                cerr << "The markers for the cells of dimension 1 were not stored correctly." << endl;
                cerr << "The marker not stored correctly is the one with id: " << id << endl;
                return false;
            }
        }
        
        return true;
    }

    bool Cell2DsMarkersAreCorrect(PolygonalMesh& mesh){
        vector<int> markersCell2DsCorrect = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        /* Checking each element of the two vectors and comparing them: if something's not equal, the function returns 
        false and stops, printing on the standard output the id of the markerthat  was not stored properly */
        for(unsigned int id = 0; id < markersCell2DsCorrect.size(); id++){
            if(markersCell2DsCorrect[id] != mesh.Cell2DsMarkers[id]){
                cerr << "The markers for the cells of dimension 2 were not stored correctly." << endl;
                cerr << "The marker not stored correctly is the one with id: " << id << endl;
                return false;
            }
        }
        
        return true;
    }

    bool EdgesLengthsAreGreaterThanTolerance(PolygonalMesh& mesh, const double& tolerance){
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
            if(length <= tolerance){
                cerr << "Not all edges are greater than 0." << endl;
                cerr << "The edge that has length equal to 0 is the one with id: " << id << endl;
                cerr << "Is the tolerance " << tolerance << " perhaps excessively small?" << endl;
                return false;
            }
        }
        return true;
    }

    bool PolygonsAreasAreGreaterThanToleranceSquared(PolygonalMesh& mesh, const double& tolerance){
        /* Testing the area of the polygons dividing them into triangles with a common vertex that is the barycenter of the polygon.
        In order to ccalculate the area, I decided to use the Heron's formula. */
        for(unsigned int id = 0; id < mesh.NumCell2Ds; id++){
            int numVertices = mesh.Cell2DsVertices[id].size();
            vector<int> ids_points(numVertices, 0);
            vector<double> x_coordinates(numVertices, 0);
            vector<double> y_coordinates(numVertices, 0);
            double sum_x_coordinates = 0.0;
            double sum_y_coordinates = 0.0;
            for(int vertex = 0; vertex < numVertices; vertex++){

                /* Saving the ids of each vertex */
                ids_points[vertex] = mesh.Cell2DsVertices[id][vertex];
                int id_point = ids_points[vertex];

                /* Saving the coordinates of each vertex */
                x_coordinates[vertex] = mesh.Cell0DsCoordinates(0, id_point);
                y_coordinates[vertex] = mesh.Cell0DsCoordinates(1, id_point); 
                sum_x_coordinates += x_coordinates[vertex];
                sum_y_coordinates += y_coordinates[vertex];
            }

            /* Calculating the barycenter */
            double barycenter_x_coordinate = sum_x_coordinates / double(numVertices);
            double barycenter_y_coordinate = sum_y_coordinates / double(numVertices);

            /* The number of vertices inside the polygon is equal to the number of traingles inside it, 
            so we can use the number of vertices ijnstead of the edges to cycle and compute the area of each triangle. */
            double area_of_polygon = 0.0;
            for(int vertex = 0; vertex < numVertices; vertex++){
                double x_difference_21 = 0.0;
                double y_difference_21 = 0.0;
                double x_difference_31 = 0.0;
                double y_difference_31 = 0.0;
                double x_difference_32 = 0.0;
                double y_difference_32 = 0.0;
                if(vertex < numVertices - 1){
                    x_difference_21 = x_coordinates[vertex] - barycenter_x_coordinate;
                    y_difference_21 = y_coordinates[vertex] - barycenter_y_coordinate;
                    x_difference_31 = x_coordinates[vertex + 1] - barycenter_x_coordinate;
                    y_difference_31 = y_coordinates[vertex + 1] - barycenter_y_coordinate;
                    x_difference_32 = x_coordinates[vertex + 1] - x_coordinates[vertex];
                    y_difference_32 = y_coordinates[vertex + 1] - y_coordinates[vertex];
                }

                // The last vertex of the polygon and the barycenter also create a triangle with the first vertex of the polygon.
                else{
                    x_difference_21 = x_coordinates[vertex] - barycenter_x_coordinate;
                    y_difference_21 = y_coordinates[vertex] - barycenter_y_coordinate;
                    x_difference_31 = x_coordinates[0] - barycenter_x_coordinate;
                    y_difference_31 = y_coordinates[0] - barycenter_y_coordinate;
                    x_difference_32 = x_coordinates[0] - x_coordinates[vertex];
                    y_difference_32 = y_coordinates[0] - y_coordinates[vertex];
                }

                // Calculating the area of each triangle with the Heron's formula
                double length_21 = sqrt(x_difference_21 * x_difference_21 + y_difference_21 * y_difference_21);
                double length_31 = sqrt(x_difference_31 * x_difference_31 + y_difference_31 * y_difference_31);
                double length_32 = sqrt(x_difference_32 * x_difference_32 + y_difference_32 * y_difference_32);
                double semiperimeter = 0.5 * (length_21 + length_31 + length_32);

                area_of_polygon += sqrt(semiperimeter * (semiperimeter - length_21) * (semiperimeter - length_31) * (semiperimeter - length_32));
            }
            
            if(area_of_polygon <= (tolerance * tolerance)){
                cerr << "Not all polygons have area greater than 0." << endl;
                cerr << "The polygon that could have area equal to 0 is the one with id: " << id 
                << ". It needs further investigation" << endl;
                cerr << "Is the tolerance " << tolerance << " perhaps excessively small?" << endl;
                return false;
            }
        }

        return true;
    }

}

