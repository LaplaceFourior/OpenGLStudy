#pragma once
#include <memory>
#include "Mesh.h"

namespace TenetEngine {

class MeshFactory
{
public:
    static void Init();
    static std::shared_ptr<Mesh> GetBoxMesh();
};

}