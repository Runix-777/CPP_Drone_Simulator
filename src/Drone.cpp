#include <simulator/Drone.hpp>
#include <simulator/Rotor.hpp>
#include <utility/raylibext.h>
#include <rlgl.h>
#include <iostream>
Drone::Drone(glm::vec3 startPos, glm::vec3 orientation, float mass, float drag_coefficient,std::vector<Rotor> rotors ): 
    MovingEntity(startPos,orientation, mass, drag_coefficient),
    rotors_(std::move(rotors)),
    throttle_input_(0.0f),
    roll_input_(0.0f),
    pitch_input_(0.0f),
    yaw_input_(0.0f)
    {   
        computeInertiaTensor();
     }

float Drone::ComputeTotalMass() const {
    float totalMass = mass_;
    for (const auto& rotor : rotors_) {
        totalMass += rotor.getMass();
    }
    return totalMass;
}

void Drone::sendControlInputs() {
    if (rotors_.empty()) return;
    if (rotors_.size() == 4) {
        rotors_[0].setThrottle(throttle_input_ + pitch_input_ + roll_input_ - yaw_input_); //Front left
        rotors_[1].setThrottle(throttle_input_ + pitch_input_ - roll_input_ + yaw_input_); //Front right
        rotors_[2].setThrottle(throttle_input_ - pitch_input_ + roll_input_ + yaw_input_); //Rear left
        rotors_[3].setThrottle(throttle_input_ - pitch_input_ - roll_input_ - yaw_input_); //Rear right
    }
    return;
    
}
void Drone::computeInertiaTensor() {
    glm::mat3 I(0.0f);
    for (const auto& rotor : rotors_) {
        glm::vec3 r = rotor.getLocalOffset();
        float m = rotor.getMass();
        I[0][0] += m * (r.y * r.y + r.z * r.z);
        I[1][1] += m * (r.x * r.x + r.z * r.z);
        I[2][2] += m * (r.x * r.x + r.y * r.y);

        I[0][1] += -m * r.x * r.y;
        I[0][2] += -m * r.x * r.z;
        I[1][0] += -m * r.y * r.x;
        I[1][2] += -m * r.y * r.z;
        I[2][0] += -m * r.z * r.x;
        I[2][1] += -m * r.z * r.y;
    }
    inertia_tensor = I;
    inv_inertia_tensor_ = glm::inverse(I);

}


void Drone::update(float dt) {
    // Update each rotor
    sendControlInputs();
    glm::vec3 Fthrust_local(0.0f);
    glm::vec3 total_pitch_roll_torque(0.0f);
    glm::vec3 total_yaw_torque(0.0f);
    for (auto& rotor : rotors_) {
        rotor.update(dt);
        Fthrust_local += glm::vec3(0.0f, 0.0f, rotor.getCurrentThrust());
        total_pitch_roll_torque += glm::cross(rotor.getLocalOffset(), glm::vec3(0.0f, 0.0f, rotor.getCurrentThrust()));
        total_yaw_torque += glm::vec3(0.0f, 0.0f, rotor.getCurrentTorque());
    }
    std::cout << "Fthrust_local: " << Fthrust_local.x << ", " << Fthrust_local.y << ", " << Fthrust_local.z << std::endl;
    std::cout << "total_pitch_roll_torque: " << total_pitch_roll_torque.x << ", " << total_pitch_roll_torque.y << ", " << total_pitch_roll_torque.z << std::endl;
    std::cout << "total_yaw_torque: " << total_yaw_torque.x << ", " << total_yaw_torque.y << ", " << total_yaw_torque.z << std::endl;
    float totalMass = ComputeTotalMass(); // Compute total mass including rotors
    // Compute all forces acting on the drone
    // Convert local thrust to world coordinates    
    glm::mat3 R = glm::mat3(getRotationMatrix());
    glm::vec3 Fthrust_world = R * Fthrust_local;
    // Gravity
    glm::vec3 Fg(0.0f, 0.0f,-totalMass * 9.81f); //Gravity Force
    // Drag
    glm::vec3 Fdrag = -drag_coefficient_ * velocity_ * glm::length(velocity_); // Drag Force
    // Sum all forces
    glm::vec3 Ftotal = Fthrust_world  + Fdrag + Fg;
    // Update linear motion using Newton's second law
    glm::vec3 acceleration = Ftotal / totalMass;


    // Compute angular acceleration using Euler's equations for rigid body rotation
    glm::vec3 total_torque = total_pitch_roll_torque + total_yaw_torque;
    glm::vec3 angular_acceleration = inv_inertia_tensor_ * (total_torque - glm::cross(angular_velocity_, inertia_tensor * angular_velocity_));

    velocity_ += acceleration * dt;
    position_ += velocity_ * dt;
    if (position_[2] < 0.0f)
        position_[2] = 0.0f;

    angular_velocity_ += angular_acceleration * dt;
    orientation_ += angular_velocity_ * dt;
}

void Drone::draw() const {
    const glm::vec3 drone_size = {1.0f, 1.0f, 0.2f};
    const glm::vec3 rotor_size = 0.5f * drone_size;

    rlPushMatrix();
    rlTranslatef(position_.x, position_.y, position_.z);
    rlRotatef(orientation_.z * RAD2DEG, 0.0f, 0.0f, 1.0f);
    rlRotatef(orientation_.y * RAD2DEG, 0.0f, 1.0f, 0.0f);
    rlRotatef(orientation_.x * RAD2DEG, 1.0f, 0.0f, 0.0f);

    DrawCubeV(toRaylibVec3(glm::vec3(0.0f, 0.0f, 0.0f)), toRaylibVec3(drone_size) , RED); // Draw the drone as a red cube for simplicity
    // Draw each rotor
    for (const auto& rotor : rotors_) {
        glm::vec3 local_offset = rotor.getLocalOffset();
        glm::vec3 sign = glm::sign(local_offset);
        DrawCubeV(toRaylibVec3(local_offset+0.5f*sign*drone_size), toRaylibVec3(rotor_size), BLUE);
    }
    rlPopMatrix();
}

void Drone::setControlInputs(float throttle, float roll, float pitch, float yaw) {
    throttle_input_ = throttle;
    roll_input_ = roll;
    pitch_input_ = pitch;
    yaw_input_ = yaw;
}
