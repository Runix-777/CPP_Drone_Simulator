#pragma once

#include <glm/glm.hpp>

class Rotor {
    private:
        //FIXED CONSTANTS
        glm::vec3 local_offset_;  //3D vector
        float mass_;                //kg
        float max_thrust_;           //Newton
        float max_rpm_;              //Revolution per min
        float torque_coefficient_;       // Torque coefficient for the rotor
        float spin_direction_;           // -1.0 CCW or 1.0 CW
        float spin_up_rate_;           // Spin up rate for the rotor

        //DYNAMIC STATE VARIABLES
        //Command state input
        float throttle_; //Normalized between 0.0f and 1.0f
        //Physical state input
        float current_thrust_;      //Newton
        float current_torque_;        //Newton meter
        float current_rpm_;         //Revolution per min
        //Visual state input
        float current_angle_;

    public:

        Rotor(glm::vec3 local_offset, float mass, float max_thrust,float max_rpm, float torque_coefficient, float spin_direction, float spin_up_rate);
        void update(float dt);

        //GETTERS
        float getCurrentThrust() const;
        float getCurrentTorque() const;
        glm::vec3 getLocalOffset() const;
        float getCurrentAngle() const;
        float getCurrentRPM() const;
        float getThrottle() const;
        //SETTERS
        void setThrottle(float throttle);
        void setSpinDirection(float direction);
        void setTorqueCoefficient(float torque_coefficient);
        void setSpinUpRate(float spin_up_rate);



};