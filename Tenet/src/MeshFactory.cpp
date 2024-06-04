#include "MeshFactory.h"
#include "Mesh.h"

using namespace TenetEngine;

// a box centered at the origin 
std::vector<Vertex> boxVertices = {
    // position             // texture coordinate  // normal 
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}}, // front 
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}}, // back
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}}, // left
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}}, // right
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}}, // up
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}}, // down
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}}
};
// every face's index is the same
std::vector<TriangleIndex> boxTriangleIndices = {
    {0 , 1 , 2 },// front
    {0 , 2 , 3 },
    {4 , 5 , 6 },// back
    {4 , 6 , 7 },
    {8 , 9 , 10},// left
    {8 , 10, 11},
    {12, 13, 14},// right
    {12, 14, 15},
    {16, 17, 18},// up
    {16, 18, 19},
    {20, 21, 22},// down
    {20, 22, 23}
};

std::shared_ptr<Mesh> sBoxMesh = nullptr;

void MeshFactory::Init()
{
    sBoxMesh = std::make_shared<Mesh>(boxVertices, boxTriangleIndices);
}

std::shared_ptr<Mesh> MeshFactory::GetBoxMesh()
{
    return sBoxMesh;
}

