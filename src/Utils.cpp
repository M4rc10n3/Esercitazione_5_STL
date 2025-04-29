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

}

