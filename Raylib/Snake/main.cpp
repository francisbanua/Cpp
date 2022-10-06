#include "raylib.h"

const int screenWidth = 450;
const int screenHeight = 450;
bool gameOver;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
Rectangle head;
Rectangle fruit;
const int sWidth = 20;
const int sHeight = 20;

void Setup_() {
    gameOver = false;
    dir = STOP;
    x = screenWidth / 2 - sWidth / 2;
    y = screenHeight / 2 - sHeight / 2;
    fruitX = GetRandomValue(sWidth, screenWidth - sWidth);
    fruitY = GetRandomValue(sHeight, screenHeight - sHeight);
    score = 0;
}

void Draw_() {
    DrawRectangleRec(head, BLUE);
    DrawRectangleRec(fruit, RED);
}

void Input_() {
    if (IsKeyPressed(KEY_W)) {
        dir = UP;
    }
    if (IsKeyPressed(KEY_A)) {
        dir = LEFT;
    }
    if (IsKeyPressed(KEY_S)) {
        dir = DOWN;
    }
    if (IsKeyPressed(KEY_D)) {
        dir = RIGHT;
    }
}

void Logic_() {
    switch (dir) {
        case UP:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
    }
    head = {(float) x, (float) y, sWidth, sHeight};
    if (CheckCollisionRecs(head, fruit)) {
        fruitX = GetRandomValue(0, screenWidth - sWidth);
        fruitY = GetRandomValue(0, screenHeight - sHeight);
    }
    fruit = {(float) fruitX, (float) fruitY, sWidth, sHeight};
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Snake");

    Setup_();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Input_();
        Logic_();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Draw_();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}