#include <simulator/Rotor.hpp>
#include <iostream>

void printRotorState(const Rotor& rotor) {
    std::cout << "Throttle: " << rotor.getThrottle() << std::endl;
    std::cout << "Current RPM: " << rotor.getCurrentRPM() << std::endl;
    std::cout << "Current Thrust: " << rotor.getCurrentThrust() << std::endl;
    std::cout << "Current Torque: " << rotor.getCurrentTorque() << std::endl;
    std::cout << "Local Offset: (" << rotor.getLocalOffset().x << ", " << rotor.getLocalOffset().y << ", " << rotor.getLocalOffset().z << ")" << std::endl;
    std::cout << "Current Angle: " << rotor.getCurrentAngle() << std::endl;
    std::cout << "------------------------" << std::endl;
    
}

int main() {

    float dt = 0.1f; //
    float current_time = 0.0f;
    //Rotor::Rotor(glm::vec3 local_offset, float mass, float max_thrust,float max_rpm, float torque_coefficient, float spin_direction, float spin_up_rate)
    Rotor rotor1(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 10.0f, 1000.0f, 0.1f, 1.0f, 0.5f);

    while (current_time < 1.0f) {
        rotor1.update(dt);
        rotor1.setThrottle(1.0f); // Set throttle to maximum for testing
        printRotorState(rotor1);
        current_time += dt;
    }
}