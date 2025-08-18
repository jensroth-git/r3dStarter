#include <raylib.h>
#include <iostream>

int main() {
    // Initialize raylib window
    const auto window_width = 800;
    const auto window_height = 600;
    InitWindow(window_width, window_height, "Hello Raylib!");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        const auto text = "Hello, Raylib!";
        const auto text_width = MeasureText(text, 20);
        const auto text_height = 20;

        DrawText(text, window_width / 2 - text_width / 2, window_height / 2 - text_height / 2, text_height, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
} 