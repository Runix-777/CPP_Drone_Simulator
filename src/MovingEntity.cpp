#include "MovingEntity.hpp"

MovingEntity::MovingEntity(glm::vec3 startPos):
    Entity(startPos),
    velocity_(0.0f),
    acceleration_(0.0f)
    {

    }

    glm::vec3 MovingEntity::getVelocity() const{
        return velocity_;
    }

    glm::vec3 MovingEntity::getAcceleration() const{
        return acceleration_;
    }