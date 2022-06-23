/*******************************************************************************************
*
*   raylib [shaders] example - mesh instancing
*
*   This example has been created using raylib 3.7 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by @seanpringle and reviewed by Max (@moliad) and Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2020-2022 @seanpringle, Max (@moliad) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/


#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include <stdlib.h>         // Required for: calloc(), free()
#include <math.h>           // Required for: 

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define MAX_INSTANCES  8000

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - mesh instancing");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ -125.0f, 125.0f, -125.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Define mesh to be instanced
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);

    // Define transforms to be uploaded to GPU for instances
    Matrix *transforms = (Matrix *)RL_CALLOC(MAX_INSTANCES, sizeof(Matrix));   // Pre-multiplied transformations passed to rlgl

    // Translate and rotate cubes randomly
    for (int i = 0; i < MAX_INSTANCES; i++)
    {
        Matrix translation = MatrixTranslate((float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50));
        Vector3 axis = Vector3Normalize((Vector3){ (float)GetRandomValue(0, 360), (float)GetRandomValue(0, 360), (float)GetRandomValue(0, 360) });
        float angle = (float)GetRandomValue(0, 10)*DEG2RAD;
        Matrix rotation = MatrixRotate(axis, angle);
        
        transforms[i] = MatrixMultiply(rotation, translation);
    }

    // Load lighting shader
    Shader shader = LoadShader(TextFormat("resources/shaders/glsl%i/lighting_instancing.vs", GLSL_VERSION),
                               TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get shader locations
    shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

    // Set shader value: ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, SHADER_UNIFORM_VEC4);

    // Create one light
    CreateLight(LIGHT_DIRECTIONAL, (Vector3){ 50.0f, 50.0f, 0.0f }, Vector3Zero(), WHITE, shader);

    // NOTE: We are assigning the intancing shader to material.shader
    // to be used on mesh drawing with DrawMeshInstanced()
    Material matInstances = LoadMaterialDefault();
    matInstances.shader = shader;
    matInstances.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    // Create a defult material with default internal shader for non-instanced mesh drawing
    Material matDefault = LoadMaterialDefault();
    matDefault.maps[MATERIAL_MAP_DIFFUSE].color = BLUE;

    // Set an orbital camera mode
    SetCameraMode(camera, CAMERA_ORBITAL);  

    SetTargetFPS(60);                      // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);

        // Update the light shader with the camera view position
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw cube mesh with default material (BLUE)
                DrawMesh(cube, matDefault, MatrixTranslate(-10.0f, 0.0f, 0.0f));

                // Draw meshes instanced using material containing instancing shader (RED + lighting),
                // transforms[] for the instances should be provided, they are dynamically
                // updated in GPU every frame, so we can animate the different mesh instances
                DrawMeshInstanced(cube, matInstances, transforms, MAX_INSTANCES);

                // Draw cube mesh with default material (BLUE)
                DrawMesh(cube, matDefault, MatrixTranslate(10.0f, 0.0f, 0.0f));

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_FREE(transforms);    // Free transforms

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
