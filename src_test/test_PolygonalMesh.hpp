#pragma once

#include <vector>
#include <cmath>
#include <gtest/gtest.h>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;

TEST(TestPolygonalMesh, TestMarkersCell0Ds){
    vector<int> v(mesh.Cell0DsMarkers);
    vector<int> markers_correct = {1, 2, 3, 4, 0, 8, 5, 6, 7, 0, 0, 0, 0, 0, 0, 8, 5, 6, 0, 0, 7, 
        8, 6, 7, 5, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    EXPECT_EQ(v, markers_correct);
}

TEST(TestPolygonalMesh, TestMarkersCell1Ds){
    vector<int> v(mesh.Cell1DsMarkers);
    vector<int> markers_correct = {0, 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 8, 0, 0, 7, 0, 0, 7, 0, 5, 0, 
        0, 5, 6, 7, 8, 6, 0, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    EXPECT_EQ(v, markers_correct);
}

TEST(TestPolygonalMesh, TestMarkersCell2Ds){
    vector<int> v(mesh.Cell2DsMarkers);
    vector<int> markers_correct = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    EXPECT_EQ(v, markers_correct);
}

TEST(TestPolygonalMesh, TestEdges){
    int NumEdges = mesh.NumCell1Ds;
    vector<double> lengths(NumEdges, 0.0);
    /* Saving the length of each edge in the vector "lengths" */
    for(unsigned int id = 0; id < NumEdges; id++){
        int id_point_1 = mesh.Cell1DsExtrema(0, id);
        int id_point_2 = mesh.Cell1DsExtrema(1, id);
        double x_point_1 = mesh.Cell0DsCoordinates(0, id_point_1);
        double y_point_1 = mesh.Cell0DsCoordinates(1, id_point_1);
        double x_point_2 = mesh.Cell0DsCoordinates(0, id_point_2);
        double y_point_2 = mesh.Cell0DsCoordinates(1, id_point_2);
        
        double x_difference = x_point_2 - x_point_1;
        double y_difference = y_point_2 - y_point_1;
        lengths[id] = sqrt(x_difference * x_difference + y_difference * y_difference);
    }

    /* Creating a vector of only zeros with the same dimension of the vector "length" */
    vector<double> zero_lengths(NumEdges, 0.0);

    EXPECT_GT(lengths, zero_lengths)
}

/* TEST(TestPolygonalMesh, TestPolygons){
    /* Verificare solo che ogni poligono contenga un triangolo che ha area maggiore di 0, sfruttando 
    o i vertici o i lati del poligono dati nel file Cell2Ds.csv e la formula di Erone per calcolarne 
    l'area senza aver bisogno di trovare altezze o consimili }*/
