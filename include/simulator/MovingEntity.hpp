#pragma once
#include "Entity.hpp"

class MovingEntity : public Entity {
    protected:
        glm::vec3 velocity_;
        glm::vec3 acceleration_;
        
        glm::vec3 angular_velocity_; // (x=roll rate, y=pitch rate, z=yaw rate)
        glm::vec3 angular_acceleration_;
        glm::mat3 inertia_tensor; 

        float drag_coefficient_;
        float mass_;


    
    public:
        MovingEntity(glm::vec3 startPos,glm::vec3 orientation, float mass, float drag_coefficient);

        virtual ~MovingEntity() = default;

        glm::vec3 getVelocity() const;
        glm::vec3 getAcceleration() const;
        glm::vec3 getAngularVelocity() const;
        glm::vec3 getAngularAcceleration() const;
        glm::mat3 getInertiaTensor() const;
        void update(float dt) override = 0;
        virtual void computeInertiaTensor() = 0;
};