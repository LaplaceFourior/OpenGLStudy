#pragma once
#include <glad/glad.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// actually, only box mesh now (owo)

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

struct TriangleIndex {
    unsigned int one;
    unsigned int two;
    unsigned int three;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndex>& indices);
    ~Mesh();
public:
    void draw();
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int mIndicesLength;
};