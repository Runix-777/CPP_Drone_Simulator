#include "simulator/Drone.hpp"


int main() {
    std::vector<Rotor> rotors;
    // Initialize rotors
    //Front-Left Rotor
    Rotor rotor1(glm::vec3(1.0f, 1.0f, 0.0f), 0.40f, 18.6f, 3141.0f, 0.2f, 1.0f, 30.0f);
    rotors.push_back(rotor1);
    //Front-Right Rotor
    Rotor rotor2(glm::vec3(1.0f, -1.0f, 0.0f), 0.40f, 18.6f, 3141.0f, 0.2f, -1.0f, 30.0f);
    rotors.push_back(rotor2);
    //Rear-Left Rotor
    Rotor rotor3(glm::vec3(-1.0f, 1.0f, 0.0f), 0.40f, 18.6f, 3141.0f, 0.2f, -1.0f, 30.0f);
    rotors.push_back(rotor3);
    //Rear-Right Rotor
    Rotor rotor4(glm::vec3(-1.0f, -1.0f, 0.0f), 0.40f, 18.6f, 3141.0f, 0.2f, 1.0f, 30.0f);
    rotors.push_back(rotor4);

    // Create a drone with the initialized rotors
    Drone drone(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.500f, 0.5f, rotors);

    // Send control inputs to the drone
    

    return 0;
}