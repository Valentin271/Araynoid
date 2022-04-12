#include "raylib.h"

#include "game.h"

#ifdef PLATFORM_WEB
#include "emscripten.h"
#endif


void UpdateDrawFrame()
{
    UpdateFrame();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawFrame();

    EndDrawing();
}


int main()
{
#ifndef DEBUG
    SetTraceLogLevel(LOG_NONE);
#endif

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Araynoid");
    SetExitKey(KEY_NULL);

    InitGame();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

#endif

    CloseWindow();

    return 0;
}
