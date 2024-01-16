#include "BaseMesh.h"
#include <glad/glad.h>


void BaseMesh::bindVertexObjects()
{
    glBindVertexArray(m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseMesh::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void BaseMesh::unbindVertexObjects()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseMesh::destroyVertexObjects()
{
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
}

