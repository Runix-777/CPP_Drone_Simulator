#include "MovingEntity.hpp"
#include <vector>
#include "Rotor.hpp"

class Drone : public MovingEntity {
    private:
        std::vector<Rotor> rotors_;
        glm::mat3 inv_inertia_tensor_;
        
        //command
        float throttle_input_;
        float roll_input_;
        float pitch_input_;
        float yaw_input_;

        float ComputeTotalMass() const;
        void sendControlInputs();
    public:

        Drone(glm::vec3 startPos,glm::vec3 orientation, float mass,float drag_coefficient, std::vector<Rotor> rotors);
    
        void update(float dt) override;
        void draw() const override;
        void computeInertiaTensor() override;

        void setControlInputs(float throttle, float roll, float pitch, float yaw);
        
        


};