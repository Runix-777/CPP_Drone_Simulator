#include <simulator/Rotor.hpp>


Rotor::Rotor(glm::vec3 local_offset, float mass, float max_thrust,float max_rpm, float torque_coefficient, float spin_direction, float spin_up_rate):
    local_offset_(local_offset),
    mass_(mass),
    max_thrust_(max_thrust),
    max_rpm_(max_rpm),
    torque_coefficient_(torque_coefficient),
    spin_direction_(spin_direction),
    spin_up_rate_(spin_up_rate),

    throttle_(0.0f),
    current_thrust_(0.0f),
    current_torque_(0.0f),
    current_rpm_(0.0f),
    current_angle_(0.0f)
    {}

// Update the rotor's state based on the elapsed time dt
void Rotor::update(float dt) {
    float target_rpm = throttle_ * max_rpm_;
    current_rpm_ += (target_rpm - current_rpm_) * spin_up_rate_ * dt;
    current_thrust_ = max_thrust_ * (current_rpm_ / max_rpm_) * (current_rpm_ / max_rpm_); //lift
    current_torque_ = current_thrust_ * torque_coefficient_ * spin_direction_; //rotation
    current_angle_ += current_rpm_ * 6.0f * dt; // Update angle based on RPM and time delta
    if (current_angle_ > 360.0f) current_angle_ -= 360.0f;  
}
    
//GETTERS
float Rotor::getCurrentThrust() const {
    return current_thrust_;
}

float Rotor::getCurrentTorque() const {
    return current_torque_;
}

float Rotor::getCurrentRPM() const {
    return current_rpm_;
}

float Rotor::getThrottle() const {
    return throttle_;
}

glm::vec3 Rotor::getLocalOffset() const {
    return local_offset_;
}

float Rotor::getCurrentAngle() const {
    return current_angle_;
}
    
//SETTERS
void Rotor::setThrottle(float throttle) {
    throttle_ = throttle;
}

void Rotor::setSpinDirection(float direction) {
    spin_direction_ = direction;
}

