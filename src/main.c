#include "raylib.h"

#include "game.h"

#ifdef PLATFORM_WEB
#include "emscripten.h"
#endif


//--------------------
// GLOBAL VARIABLES
//--------------------

// Misc
bool pause;
bool borderless;

Font scoreFont;

bool showDebug;

// Level
level currentLvl;
short OUTLINE_WIDTH;

#ifdef DEBUG
levelDebug_t lvlDebug;
#endif

// Bricks
int BRICK_WIDTH;
int BRICK_HEIGHT;

// Player
player_t player;

// Ball
float BALL_SPEED;
float BALL_RADIUS;
ball_t ball;

//--------------------
// FUNCTIONS
//--------------------

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

    UnloadGame();
    CloseWindow();

    return 0;
}
