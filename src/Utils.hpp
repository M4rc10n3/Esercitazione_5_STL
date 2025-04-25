#pragma once

#include <string>
#include "PolygonalMesh.hpp"

namespace PolygonalLibrary{
    
    bool ImportMesh(PolygonalMesh& mesh, 
        const string& Cell0DsFilePath = {},
        const string& Cell1DsFilePath = {},
        const string& Cell2DsFilePath = {});

    bool ImportCell0Ds(const string& filePath, PolygonalMesh& mesh);

    bool ImportCell1Ds(const string& filePath, PolygonalMesh& mesh);

    bool ImportCell2Ds(const string& filePath, PolygonalMesh& mesh);

}

