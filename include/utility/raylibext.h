#pragma once
#include "raylib.h"
#include <glm/glm.hpp>

inline Vector3 toRaylibVec3(const glm::vec3& v) {
    return Vector3{v.x, v.y, v.z};
}