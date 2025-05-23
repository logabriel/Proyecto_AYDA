#include "Wfc3D.hpp"
#include "Visualization.hpp"
// #include <optional>

void display_scene_from_matrix(Wfc3D wfc3d, std::vector<Color> display_colors)
{

#pragma region Visual Setup
    const int screenWidth = 1000;
    const int screenHeight = 800;

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
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }

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
                            Color cell_color = display_colors[pattern - 1];
                            Vector3 cube_pos = {static_cast<float>(offset_to_center_x - x), static_cast<float>(z), static_cast<float>(offset_to_center_y - y)};
                            DrawCube(cube_pos, 1.0f, 1.0f, 1.0f, cell_color);
                            DrawCubeWires(cube_pos, 1.0f, 1.0f, 1.0f, BLACK);
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

void display_scene_from_matrix(std::vector<std::vector<std::vector<std::set<unsigned int>>>> matrix3D, std::vector<Color> display_colors)
{
#pragma region Visual Setup
    const int screenWidth = 1000;
    const int screenHeight = 800;

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
    // auto [size_x, size_y, size_z] = wfc3d.getSizes();
    auto size_x = matrix3D.size();
    auto size_y = matrix3D[0].size();
    auto size_z = matrix3D[0][0].size();
    // auto matrix3D = wfc3d.getMatrix3D();
    auto offset_to_center_x = size_x / 2;
    auto offset_to_center_y = size_y / 2;
    auto offset_to_center_z = size_z / 2;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }

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
                            Color cell_color = display_colors[pattern - 1];
                            Vector3 cube_pos = {static_cast<float>(offset_to_center_x - x), static_cast<float>(z), static_cast<float>(offset_to_center_y - y)};
                            DrawCubeWires(cube_pos, 1.0f, 1.0f, 1.0f, BLACK);
                            DrawCube(cube_pos, 1.0f, 1.0f, 1.0f, cell_color);
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