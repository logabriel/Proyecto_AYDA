
#include "Wfc3D.hpp"
#include "visualization.hpp"
int raylib_demo()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Create the window and OpenGL context
    InitWindow(1280, 800, "Hello Raylib");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture wabbit = LoadTexture("wabbit_alpha.png");

    // game loop
    while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
    {
        // drawing
        BeginDrawing();

        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLACK);

        // draw some text using the default font
        DrawText("Hello Raylib", 200, 200, 20, WHITE);

        // draw our texture to the screen
        DrawTexture(wabbit, 400, 200, WHITE);

        // end the frame and get ready for the next one  (display frame, poll input, etc...)
        EndDrawing();
    }

    // cleanup
    // unload our texture so it can be cleaned up
    UnloadTexture(wabbit);

    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}

std::vector<Color> basic_colors = {
    GREEN,
    GRAY,
    BLACK,
};

void display_scene_from_matrix(Wfc3D wfc3d)
{
    auto scene = wfc3d.getMatrix3D();
    auto [size_x, size_y, size_z] = wfc3d.get_sizes();
    wfc3d.printResult();
#pragma region Visual Setup
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - geometric shapes");
    DisableCursor();
    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
#pragma endregion
    auto patterns = wfc3d.get_patterns();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        if (IsKeyPressed(KEY_F))
        {

            ToggleFullscreen();
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);
        auto box_size = 1.0f;
        auto box_dimensions = (Vector3){box_size, box_size, box_size};
        // draw matrix
        for (int i = 0; i < size_x; ++i)
        {
            for (int j = 0; j < size_y; ++j)
            {
                for (int k = 0; k < size_z; ++k)
                {
                    int val = *(scene[i][j][k].begin());
                    // auto val = patterns[curr].id;
                    if (val != 0)
                    {
                        auto position = (Vector3){
                            box_size * (float)i,
                            box_size * (float)k,
                            box_size * (float)j};
                        Color color = basic_colors[val];
                        DrawCubeV(position, box_dimensions, color);
                    }
                }
            }
        }

        DrawGrid(20, 1.0f); // Draw a grid
        EndMode3D();
        // DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}