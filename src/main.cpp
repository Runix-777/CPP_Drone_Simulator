#include "raylib.h"

int main(void)
{
	constexpr int screenWidth = 800;
	constexpr int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "example");
	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("This is my first window!",190,200,20,RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
