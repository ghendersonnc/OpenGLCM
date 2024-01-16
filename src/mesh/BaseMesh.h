#pragma once
#include <vector>
#include "../renderer/Shader.h"
class BaseMesh {
public:
    BaseMesh() = default;
    void bindVertexObjects();
    void draw() const;
    void unbindVertexObjects();
    void destroyVertexObjects();

    virtual ~BaseMesh() = default;
protected:
    unsigned int m_Vbo;
    unsigned int m_Vao;

};