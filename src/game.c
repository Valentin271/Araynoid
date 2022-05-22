#include "game.h"

void InitGame()
{
    OUTLINE_WIDTH = BASE_OUTLINE_WIDTH;

    BRICK_WIDTH = BASE_BRICK_WIDTH;
    BRICK_HEIGHT = BASE_BRICK_HEIGHT;

    LoadLevel(1);
    pause = false;
    borderless = false;

    scoreFont = LoadFont("resources/fonts/PressStart2P-Regular.ttf");

    playerSprite = LoadTexture("resources/sprites/player.png");
    playerLaserSprite = LoadTexture("resources/sprites/playerLaser.png");

    showDebug = false;

    InitPlayer(); // NOTE: Player init must come before ball for ballOffset
    InitBall();
    InitBonus();

    HideCursor();

#ifdef DEBUG
    lvlDebug.debugging = false;
    lvlDebug.index = 0;
#endif
}

void UnloadGame()
{
    UnloadFont(scoreFont);

    UnloadTexture(playerSprite);
    UnloadTexture(playerLaserSprite);

    DestroyBall();
}

void UpdateFrame()
{
#ifdef DEBUG
    if (IsKeyPressed(KEY_L)) {
        if (lvlDebug.debugging) {
            int loadLvl = atoi(lvlDebug.buffer);

            LoadLevel(loadLvl);

            lvlDebug.index = 0;
            strcpy(lvlDebug.buffer, "  ");
            lvlDebug.debugging = false;
            InitBall();
        } else {
            lvlDebug.debugging = true;
        }
    }

    int key = GetKeyPressed();
    if (lvlDebug.debugging) {
        if (key >= 48 && key <= 57) {
            lvlDebug.buffer[lvlDebug.index++] = key;
        } else if (key >= 320 && key <= 329) {
            // So that we can use keypad, 320 maps to 49
            key -= 271;
            lvlDebug.buffer[lvlDebug.index++] = key;
        }
    }
#endif

    if (IsKeyPressed(KEY_F3)) {
        showDebug = !showDebug;
    }

    if (IsKeyPressed(KEY_F11)) {
        ToggleBorderless();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        pause = !pause;
    }

    if (pause) return;

    // TODO: Check level end only after brick break
    if (IsLevelCleared()) {
        LoadLevel(currentLvl.number + 1);
        ResetPlayer();
        InitBonus();
        InitBall();
    }

    UpdateBall();
    UpdateLevel();
    UpdateBonus();
    UpdatePlayer();
}

void DrawFrame()
{
    DrawLevel();

    DrawOutline();
    DrawBall();
    DrawPlayer();
    DrawBonus();
    DrawScore();

    if (showDebug) {
        DrawDebug();
    }

    if (pause) {
        DrawT(
            "Pause",
            (LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH*2)/2.0f - MeasureT("Pause", 60).x/2,
            GetScreenHeight()/2 - 30,
            60,
            RAYWHITE
        );
    }
}

void DrawOutline()
{
    DrawRectangle(0, 0, OUTLINE_WIDTH, GetScreenHeight(), GRAY);
    DrawRectangle(0, 0, LEVEL_WIDTH*BRICK_WIDTH + 2*OUTLINE_WIDTH, OUTLINE_WIDTH, GRAY);
    DrawRectangle(LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH, 0, OUTLINE_WIDTH, GetScreenHeight(), GRAY);

    if (bonus_break) {
        DrawRectangle(
            LEVEL_WIDTH*BRICK_WIDTH + OUTLINE_WIDTH,
            GetScreenHeight() - BASE_PLAYER_WIDTH,
            OUTLINE_WIDTH,
            BASE_PLAYER_WIDTH,
            VIOLET
        );
    }
}

void DrawDebug()
{
    DrawFPS(20, 20);
    DrawText(TextFormat("%.3f ms", GetFrameTime()*1000.0f), 20, 40, 20, RAYWHITE);
}

void ToggleBorderless()
{
    const int monitor = GetCurrentMonitor();
    borderless = !borderless;

    if (borderless) {
        const int width = GetMonitorWidth(monitor);
        const int height = GetMonitorHeight(monitor);

        SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
        SetWindowPosition(0, 0);

        SetWindowSize(width, height);

        OUTLINE_WIDTH = 40;
        BRICK_WIDTH = width*BRICK_WIDTH/WINDOW_WIDTH;
        BRICK_HEIGHT = height*BRICK_HEIGHT/WINDOW_HEIGHT;
    } else {
        ClearWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
        SetWindowPosition(
            GetMonitorWidth(monitor)/2 - WINDOW_WIDTH/2,
            GetMonitorHeight(monitor)/2 - WINDOW_HEIGHT/2
        );

        SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

        OUTLINE_WIDTH = BASE_OUTLINE_WIDTH;
        BRICK_WIDTH = BASE_BRICK_WIDTH;
        BRICK_HEIGHT = BASE_BRICK_HEIGHT;
    }
}
