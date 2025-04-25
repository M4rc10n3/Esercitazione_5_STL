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

        mesh.Cell2DsIds.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsMarkers = Eigen::VectorXi::Zero(mesh.NumCell2Ds);
        mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
        
        cout << "mesh.Cell2DsVertices.capacity(): " << mesh.Cell2DsVertices.capacity() << endl;
        
        mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

        cout << "mesh.Cell2DsEdges.capacity(): " << mesh.Cell2DsVertices.capacity() << endl;

        char useless;
        int id;
        int NumVertices;
        int NumEdges;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;

        for(const string& line : listOfAllLines){

            istringstream inputLine(line);

            inputLine >> id >> useless
                      >> mesh.Cell2DsMarkers(id) >> useless
                      >> NumVertices;
            cout << "line " << id << ": " << line << endl;
            cout << "NumVertices: " << NumVertices << endl;
            
            mesh.Cell2DsVertices[id].reserve(NumVertices);
            cout << "mesh.Cell2DsVertices[" << id << "].capacity(): "<< mesh.Cell2DsVertices[id].capacity() << endl;
            cout << "mesh.Cell2DsVertices[" << id << "].size(): "<< mesh.Cell2DsVertices[id].size() << endl;
            vertices.resize(NumVertices);

            for(int indexVertices = 0; indexVertices < NumVertices; indexVertices++){
                inputLine >> useless >> vertices[indexVertices];
                cout << "vertices[" << indexVertices <<  "]: " << vertices[indexVertices] << endl;
            }
            cout << "Breakpoint a" << endl;
            mesh.Cell2DsVertices.push_back(vertices);
            cout << "Breakpoint b" << endl;
            for(int elementVertices = 0; elementVertices < mesh.Cell2DsVertices[id].size(); elementVertices++){
                cout << "mesh.Cell2DsVertices[" << id << "][" << elementVertices << "]: "<< mesh.Cell2DsVertices[id][elementVertices] << endl;
            }
            cout << "Everything's alright after pushing the vertices vector " << id << " back." << endl;

            inputLine >> useless >> NumEdges;
            cout << "NumEdges: " << NumEdges << endl;

            cout << "Breakpoint 1" << endl;
            // Il problema è a riga 194 (la prossima) quando si arriva alla cella con id 16
            // Creare in prova un vettore di vettori e provare a inserirci gli elementi del file all'interno 
            // per vedere se riesce a gestirli o meno
            mesh.Cell2DsEdges[id].reserve(NumEdges);
            cout << "mesh.Cell2DsEdges[" << id << "].capacity(): "<< mesh.Cell2DsEdges[id].capacity() << endl;
            cout << "mesh.Cell2DsEdges[" << id << "].size(): "<< mesh.Cell2DsEdges[id].size() << endl;
            cout << "Breakpoint 2" << endl;

            cout << "Breakpoint 3" << endl;
            edges.resize(NumEdges);
            cout << "Breakpoint 4" << endl;
            for(unsigned int indexEdges = 0; indexEdges < NumEdges; indexEdges++){
                cout << "Breakpoint 5." << indexEdges << endl;
                inputLine >> useless >> edges[indexEdges];
                cout << "edges[" << indexEdges <<  "]: " << edges[indexEdges] << endl;
            }
            mesh.Cell2DsEdges.push_back(edges);
            cout << "Breakpoint 6" << endl;
            for(unsigned int elementEdges = 0; elementEdges < mesh.Cell2DsEdges[id].size(); elementEdges++){
                cout << "mesh.Cell2DsEdges[" << id << "][" << elementEdges << "]: "<< mesh.Cell2DsEdges[id][elementEdges] << endl;
            }
            cout << "Everything's alright after pushing the edges vector " << id << " back." << endl;
            
        }

        return true;
    }

}

