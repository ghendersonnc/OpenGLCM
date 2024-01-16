#pragma once
#include <iostream>

#include "BaseMesh.h"
#include <vector>
class TriangleMesh final : public BaseMesh {
public:
    
    TriangleMesh() = default;
    void setVertexObjects();
};