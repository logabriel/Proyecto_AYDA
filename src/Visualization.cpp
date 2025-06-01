#include "Wfc3D.hpp"
#include "Visualization.hpp"

Color BG_COLOR = {109, 129, 150};
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
    bool is_cursor_enabled = true;
    bool is_wireframe_enabled = true;
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        BeginDrawing();
        ClearBackground(BG_COLOR);
        BeginMode3D(camera);
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }
        if (IsKeyPressed(KEY_G) && is_cursor_enabled)
        {
            is_cursor_enabled = false;
            DisableCursor();
        }
        if (IsKeyPressed(KEY_G) && !is_cursor_enabled)
        {
            is_cursor_enabled = true;
            EnableCursor();
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
                            if (is_wireframe_enabled)
                            {
                                DrawCubeWires(cube_pos, 1.0f, 1.0f, 1.0f, BLACK);
                            }
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
    bool is_cursor_enabled = true;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        BeginDrawing();
        ClearBackground(BG_COLOR);
        BeginMode3D(camera);
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }
        if (IsKeyPressed(KEY_G) && is_cursor_enabled)
        {
            is_cursor_enabled = false;
            DisableCursor();
        }
        if (IsKeyPressed(KEY_G) && !is_cursor_enabled)
        {
            is_cursor_enabled = true;
            EnableCursor();
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

void display_scene_from_vector(std::vector<std::tuple<unsigned, int, int, int>> vec, std::tuple<int, int, int> offset, std::vector<Color> display_colors)
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
    // camera.projection = CAMERA_ORTHOGRAPHIC;

    SetTargetFPS(60);
#pragma endregion
    bool is_cursor_enabled = true;
    bool is_wireframe_enabled = true;

    auto [offset_x, offset_y, offset_z] = offset;
    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FREE);
        // UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();
        ClearBackground(BG_COLOR);
        BeginMode3D(camera);
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }
        if (IsKeyPressed(KEY_G) && is_cursor_enabled)
        {
            is_cursor_enabled = false;
            DisableCursor();
        }
        if (IsKeyPressed(KEY_G) && !is_cursor_enabled)
        {
            is_cursor_enabled = true;
            EnableCursor();
        }
        if (IsKeyPressed(KEY_H))
        {
            is_wireframe_enabled = !is_wireframe_enabled;
        }
        for (const auto &[pattern_id, x_pos, y_pos, z_pos] : vec)
        {
            Color cell_color = display_colors[pattern_id - 1];
            Vector3 cube_pos = {static_cast<float>(offset_x - x_pos), static_cast<float>(z_pos), static_cast<float>(offset_y - y_pos)};
            DrawCube(cube_pos, 1.0f, 1.0f, 1.0f, cell_color);
            if (is_wireframe_enabled)
            {
                DrawCubeWires(cube_pos, 1.0f, 1.0f, 1.0f, BLACK);
            }
        }
        EndMode3D();
        DrawText("Toggle Fullscren (Press F)", 20, 80, 20, MAGENTA);
        // DrawText("Toggle Cursor (Press G)", 20, 20, 20, MAGENTA);
        DrawText("Toggle Wireframe (Press H)", 20, 40, 20, MAGENTA);
        EndDrawing();
    }

    CloseWindow();
}