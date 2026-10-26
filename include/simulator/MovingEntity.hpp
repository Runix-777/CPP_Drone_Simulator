#pragma once
#include "Entity.hpp"

class MovingEntity : public Entity {
    protected:
        glm::vec3 velocity_;
        glm::vec3 acceleration_;
    
    public:
        MovingEntity(glm::vec3 startPos);

        virtual ~MovingEntity() = default;

        glm::vec3 getVelocity() const;
        glm::vec3 getAcceleration() const;

        void update(float dt) override = 0; 
};