#include "raylib.h"
#include "rlgl.h"

#include <glm/glm.hpp>
#include <iostream>

#include "simulator/Drone.hpp"

int main(void)
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    //Define environment simulation constant
    constexpr float sandbox_size = 300.0f;
 
    InitWindow(screenWidth, screenHeight, "CPP Drone Simulator");
    SetTargetFPS(60);

    Camera camera = {0};
    camera.position = (Vector3){-20.0f, 20.0f, 20.0f};
    camera.target = (Vector3){0.0f, 0.0f, 15.0f};
    camera.up = (Vector3){0.0f, 0.0f, 1.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int cameraMode = CAMERA_FIRST_PERSON;
    SetTargetFPS(60);
    std::vector<Rotor> rotors;
    // Initialize rotors
    //Front-Left Rotor
    Rotor rotor1(glm::vec3(0.15f, -0.15f, 0.0f), 0.04f, 18.6f, 3141.0f, 0.02f, -1.0f, 30.0f);
    rotors.push_back(rotor1);
    //Front-Right Rotor
    Rotor rotor2(glm::vec3(0.15f, 0.15f, 0.0f), 0.04f, 18.6f, 3141.0f, 0.02f, 1.0f, 30.0f);
    rotors.push_back(rotor2);
    //Rear-Left Rotor
    Rotor rotor3(glm::vec3(-0.15f, -0.15f, 0.0f), 0.04f, 18.6f, 3141.0f, 0.02f, 1.0f, 30.0f);
    rotors.push_back(rotor3);
    //Rear-Right Rotor
    Rotor rotor4(glm::vec3(-0.15f, 0.15f, 0.0f), 0.04f, 18.6f, 3141.0f, 0.02f, -1.0f, 30.0f);
    rotors.push_back(rotor4);

    // Create a drone with the initialized rotors
    Drone drone(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 20.0f, 0.0f), 0.500f, 0.5f, rotors);
    drone.setControlInputs(0.8f, 0.0f, 0.0f, 0.0f);
    while (!WindowShouldClose()) {
        // Update drone
        drone.update(0.01);
        
        // Draw
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawCubeV((Vector3){ 0.0f, sandbox_size/2.0f, sandbox_size/4.0f }, Vector3{ sandbox_size*1.0f, 0.0f, sandbox_size*0.5f }, LIGHTGRAY);//Right wall
        DrawCubeV((Vector3){ 0.0f, -sandbox_size/2.0f, sandbox_size/4.0f }, Vector3{ sandbox_size*1.0f, 0.0f, sandbox_size*0.5f }, LIGHTGRAY);//Left wall
        DrawCubeV((Vector3){ sandbox_size/2.0f, 0.0f, sandbox_size/4.0f }, Vector3{ 0.0f, sandbox_size*1.0f, sandbox_size*0.5f }, SKYBLUE);//Front wall
        DrawCubeV((Vector3){ -sandbox_size/2.0f, 0.0f, sandbox_size/4.0f }, Vector3{ 0.0f, sandbox_size*1.0f, sandbox_size*0.5f }, SKYBLUE);//Rear wall
        // DrawCube((Vector3){ -sandbox_size, 0.0f, 0.0f }, sandbox_size, 0.0f, sandbox_size, BLACK);
        // DrawCube((Vector3){ 0.0f, sandbox_size, 0.0f }, 0.0f, sandbox_size, sandbox_size, BLACK);
        // DrawCube((Vector3){ 0.0f, -sandbox_size, 0.0f }, 0.0f, sandbox_size, sandbox_size, BLACK);
        
        DrawCubeV((Vector3){ 0.0f, 0.0f, 0.0f }, Vector3{ sandbox_size, sandbox_size, 0.0f }, GREEN); // ground
        drone.draw();
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

