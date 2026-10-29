#include <simulator/Rotor.hpp>


Rotor::Rotor(glm::vec3 local_offset, float mass, float max_thrust,float max_angular_velocity, float torque_coefficient, float spin_direction, float spin_up_rate):
    local_offset_(local_offset),
    mass_(mass),
    max_thrust_(max_thrust),
    max_angular_velocity_(max_angular_velocity),
    torque_coefficient_(torque_coefficient),
    spin_direction_(spin_direction),
    spin_up_rate_(spin_up_rate),

    throttle_(0.0f),
    current_thrust_(0.0f),
    current_torque_(0.0f),
    current_angular_velocity_(0.0f),
    current_angle_(0.0f)
    {}

// Update the rotor's state based on the elapsed time dt
void Rotor::update(float dt) {
    float target_angular_velocity = throttle_ * max_angular_velocity_;
    current_angular_velocity_ += (target_angular_velocity - current_angular_velocity_) * spin_up_rate_ * dt;
    current_thrust_ = max_thrust_ * (current_angular_velocity_ / max_angular_velocity_) * (current_angular_velocity_ / max_angular_velocity_); //lift upward force
    current_torque_ = current_thrust_ * torque_coefficient_ * spin_direction_; //rotation , around the rotor axis
    current_angle_ += current_angular_velocity_ * 180.0f / 3.14159265f * dt; // Update angle based on angular velocity and time delta
    if (current_angle_ > 360.0f) current_angle_ -= 360.0f;  
}
    
//GETTERS
float Rotor::getCurrentThrust() const {
    return current_thrust_;
}

float Rotor::getCurrentTorque() const {
    return current_torque_;
}

float Rotor::getCurrentAngularVelocity() const {
    return current_angular_velocity_;
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

float Rotor::getMass() const {
    return mass_;
}
//SETTERS
void Rotor::setThrottle(float throttle) {
    throttle_ = std::clamp(throttle, 0.0f, 1.0f);
}

void Rotor::setSpinDirection(float direction) {
    spin_direction_ = direction;
}

