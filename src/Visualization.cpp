
#include "Wfc3D.hpp"
#include "Visualization.hpp"
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
    RED,
    MAROON};

void display_scene_from_matrix(Wfc3D wfc3d)
{

#pragma region Visual Setup
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "WFC 3D Visualization");
    // DisableCursor();
    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
#pragma endregion
    auto [size_x, size_y, size_z] = wfc3d.getSizes();
    auto matrix3D = wfc3d.getMatrix3D();
    auto offset_to_center_x = size_x / 2;
    auto offset_to_center_y = size_y / 2;
    auto offset_to_center_z = size_z / 2;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        for (int z = 0; z < size_z; ++z)
        {
            for (int y = 0; y < size_y; ++y)
            {
                for (int x = 0; x < size_x; ++x)
                {
                    DrawGrid(10, 1.0f);
                    if (!matrix3D[x][y][z].empty())
                    {
                        int pattern = *matrix3D[x][y][z].begin();
                        if (pattern)
                        {
                            Color cell_color = basic_colors[pattern];
                            Vector3 cube_pos = {static_cast<float>(offset_to_center_x - x), static_cast<float>(z), static_cast<float>(offset_to_center_y - y)};
                            DrawCube(cube_pos, 1.0f, 1.0f, 1.0f, cell_color);
                            DrawCubeWires(cube_pos, 1.0f, 1.0f, 1.0f, MAGENTA);
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
}
