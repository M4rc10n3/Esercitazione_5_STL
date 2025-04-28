#pragma once 
#include "Eigen/Core"

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary{

    struct PolygonalMesh{

        unsigned int NumCell0Ds;
        vector<unsigned int> Cell0DsIds;
        VectorXi Cell0DsMarkers;
        // Eigen::Matrix3Xd Cell0DsCoordinates;
        Matrix3Xd Cell0DsCoordinates;

        unsigned int NumCell1Ds;
        vector<unsigned int> Cell1DsIds;
        VectorXi Cell1DsMarkers;
        // Eigen::Matrix2Xi Cell1DsExtrema;
        Matrix2Xi Cell1DsExtrema;

        unsigned int NumCell2Ds;
        vector<unsigned int> Cell2DsIds;
        VectorXi Cell2DsMarkers;
        /*We don't know beforehand how many vertices or edges each cell2D has, so we need a vector for each of them; because
        we don't even know how many cell2D there are we need a vector to store all of them. Therefore, we'll use a vector of vector 
        (not an Eigen matrix because, for instance, if the second row had 5 elements and the third just 3, 
        at the third row we would have 2 zeros at the end, which we don't need) */
        vector<vector<int>> Cell2DsVertices;
        vector<vector<int>> Cell2DsEdges;


    };

}
