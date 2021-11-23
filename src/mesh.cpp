#include "moxxi/core.hpp"
#include <cstring>

namespace moxxi
{
    Mesh::Mesh()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->EBO);
        glDeleteBuffers(1, &this->VBO);
    }

    std::string Mesh::strVertices()
    {
        std::string str = "[";

        std::vector<vec3>::iterator it;
        for (it = this->vertices.begin(); it != this->vertices.end(); ++it)
        {
            std::stringstream values;
            values << it->x << ", " << it->y << ", " << it->z;
            str += "(" + values.str() + ")";
            if (it + 1 != this->vertices.end())
                str += ", ";
        }
        str += "]";

        return str;
    }

    const unsigned int Mesh::vertexCount()
    {
        return this->vertices.size();
    }

    std::vector<vec3> Mesh::getVertices()
    {
        return this->vertices;
    }

    std::vector<unsigned int> Mesh::getIndices()
    {
        return this->indices;
    }

    void Mesh::updateGLBuffers()
    {
        std::vector<vec3> vertices = this->getVertices();
        std::vector<unsigned int> indices = this->getIndices();

        if (indices.size() == 0)
        {
            std::cout << "WARNING::GAMEOBJECT::updateEBO indices is empty" << std::endl;
            return;
        }

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

void Mesh::LoadMeshData(std::vector<vec3> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}

} // namespace moxxi
