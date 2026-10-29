#include "simulator/MovingEntity.hpp"

MovingEntity::MovingEntity(glm::vec3 startPos,glm::vec3 orientation, float mass, float drag_coefficient):
    Entity(startPos, orientation),
    velocity_(0.0f),
    angular_velocity_(0.0f),
    angular_acceleration_(0.0f),
    inertia_tensor(0.0f),
    acceleration_(0.0f),
    drag_coefficient_(drag_coefficient),
    mass_(mass)
    {

    }

    glm::vec3 MovingEntity::getVelocity() const{
        return velocity_;
    }

    glm::vec3 MovingEntity::getAngularVelocity() const{
        return angular_velocity_;
    }

    glm::vec3 MovingEntity::getAngularAcceleration() const{
        return angular_acceleration_;
    }

    glm::vec3 MovingEntity::getAcceleration() const{
        return acceleration_;
    }

    glm::mat3 MovingEntity::getInertiaTensor() const{
        return inertia_tensor;
    }
    