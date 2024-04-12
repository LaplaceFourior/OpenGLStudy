#pragma once
#include <memory>
#include "Mesh.h"

class MeshFactory
{
public:
    static void Init();
    static std::shared_ptr<Mesh> GetBoxMesh();
};