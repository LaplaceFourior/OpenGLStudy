#pragma once
#include <cstdint>

namespace TenetEngine {

class UUID
{
public:
    UUID() = default;
    ~UUID() = default;
public:
    bool operator==(const UUID& id) const 
    {
        return mID == id.mID;
    }
private:
    uint64_t mID;
};

}