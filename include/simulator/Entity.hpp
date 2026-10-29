#pragma once // Include guard for the Entity class header file, for example it prevents multiple definition of Entity if child classes include it.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::mat4 and transformation functions
class Entity {
    // Protected members of the Entity class, accessible by derived classes.
    protected:
        glm::vec3 position_; // Position of the entity in 3D space.
        glm::vec3 orientation_; // (x=roll,y=pitch,z=yaw)
        const uint32_t id_;
    
        static uint32_t next_id_;
    // Public members of the Entity class, accessible by every external classes
    public:
        //Class default constructor
        Entity();

        //Class parameterized constructor
        Entity(glm::vec3 start_position, glm::vec3 start_orientation);

        //Virtual Destructor to prevent memory leak
        virtual ~Entity() = default;

        //Virtual Functions, that acts like an interface
        virtual void update(float dt) = 0;
        
        //Here const = 0 act as a promise with the class: Draw won't edit the class attributes, and if so raise an error
        virtual void draw() const = 0;

        uint32_t getId() const;
        glm::vec3 getOrientation() const;
        glm::vec3 getPosition() const;
        glm::mat4 getRotationMatrix() const;
        
        void setPosition(const glm::vec3& position);
        void setOrientation(const glm::vec3& orientation);



        
};