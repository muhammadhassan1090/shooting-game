#include "raylib.h"  
#include <stdlib.h> // For random function 

// Screen dimensions
const int screenWidth = 800;
const int screenHeight = 600;

// Object dimensions and game settings
const int playerWidth = 50;
const int playerHeight = 50;
const int bulletRadius = 5;
const int objectSize = 30;
const int stoneSize = 20;

const int maxBullets = 10;
const int maxObjects = 5;
const int maxStones = 7;

// Setting Game timer
const float gameTimer = 60;

//Creating struct for different objects like bullets,targets and stones
struct Object {
    float x, y;
    bool active;
};

//creating enum for the difficulty choosen by user
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};



// Prototypes of functions that are created 
void SpawnObject(Object& obj, int screenWidth, int objectSize);
void UpdateObject(Object& obj, float speed);
bool CheckCollision(float bx, float by, float ox, float oy, float bradius, float osize);
Difficulty GetDifficulty(float& objectSpeed, float& stoneSpeed, int& targetScore, int& maxActiveStones);
void InitializeObjects(Object objects[], int size);
void ResetGameVariables(Rectangle& player, int& score, float& levelTimer, bool& difficultyChosen);
void DisplayEndGameScreen(bool& playAgain, bool won);




//start of the main function
int main() {

    InitWindow(screenWidth, screenHeight, "Shooting Game");//for creating the game window
    InitAudioDevice();//for using audio in program
    //loading the audio using the path in the memory and storing them in variables so that they can be used later
    Sound shootSound = LoadSound("mixkit-quick-positive-video-game-notification-interface-265.wav");
    Sound hitTargetSound = LoadSound("mixkit-soft-quick-punch-2151.wav");
    Sound stoneHitSound = LoadSound("mixkit-wood-hard-hit-2182.wav");


    // Loading background image and storing in variable
    Texture2D background = LoadTexture("vecteezy_arctic-frozen-sea-landscape-with-flat-ice-surface_13455070.jpg");


    // Variables for Difficulty settings of the game
    Difficulty difficulty = EASY;
    bool difficultyChosen = false;
    float objectSpeed = 2.0;
    float stoneSpeed = 1.0;
    int targetScore = 10;
    int maxActiveStones = 3;
    float levelTimer = gameTimer;


    // Settting up the Player and its speed
    Rectangle player = { screenWidth / 2.0 - playerWidth / 2.0, screenHeight - 70, playerWidth, playerHeight };
    float playerSpeed = 5.0;


    // Creating Game objects arrays and initializing their state using the function
    Object bullets[maxBullets];
    Object targets[maxObjects];
    Object stones[maxStones];
    InitializeObjects(bullets, maxBullets);
    InitializeObjects(targets, maxObjects);
    InitializeObjects(stones, maxStones);


    // Game variables
    int score = 0;
    bool playAgain = true;


    //setting the frame per second of the game
    SetTargetFPS(60);



    //start of the game loop.It continues until the window is closed or player presses Q on which the playAgain turns false. 
    while (!WindowShouldClose() && playAgain) {
        if (!difficultyChosen) {

            //taking the input from the user regarding the difficulty
            difficulty = GetDifficulty(objectSpeed, stoneSpeed, targetScore, maxActiveStones);

            // Adjust target scores based on difficulty
            if (difficulty == EASY) targetScore =20;
            if (difficulty == MEDIUM) targetScore = 40;
            if (difficulty == HARD) targetScore = 60;
            
            //for ending the if condition
            difficultyChosen = true;
            
        }

        // Controlling player movement using different inbuilt function
        if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= playerSpeed;

        // Shooting bullets
        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < maxBullets; i++) {
                if (!bullets[i].active) {
                    bullets[i].x = player.x + player.width / 2.0;
                    bullets[i].y = player.y;
                    bullets[i].active = true;
                    PlaySound(shootSound);
                    break;
                }
            }
        }

        // Update the position of the bullets
        for (int i = 0; i < maxBullets; i++) {
            if (bullets[i].active) {
                bullets[i].y -= 10.0;
                if (bullets[i].y < 0) bullets[i].active = false;
            }
        }

        // Spawn and update targets
        for (int i = 0; i < maxObjects; i++) {
            if (!targets[i].active && rand() % 100 < (difficulty == EASY ? 2 : (difficulty == MEDIUM ? 4 : 6))) {
                SpawnObject(targets[i], screenWidth, objectSize);
            }
            UpdateObject(targets[i], objectSpeed);
        }

        // Spawn and update stones
        int activeStones = 0;
        for (int i = 0; i < maxStones; i++) {
            if (!stones[i].active && rand() % 100 < (difficulty == EASY ? 1 : (difficulty == MEDIUM ? 3 : 5))) {
                if (activeStones < maxActiveStones) {
                    SpawnObject(stones[i], screenWidth, stoneSize);
                    activeStones++;
                }
            }
            UpdateObject(stones[i], stoneSpeed);
        }

        // Check collisions
        for (int i = 0; i < maxBullets; i++) {
            if (bullets[i].active) {
                // Target collisions
                for (int j = 0; j < maxObjects; j++) {
                    if (targets[j].active && CheckCollision(bullets[i].x, bullets[i].y, targets[j].x, targets[j].y, bulletRadius, objectSize)) {
                        bullets[i].active = targets[j].active = false;
                        score++;//increase score for hitting the target
                        PlaySound(hitTargetSound);
                    }
                }

                // Stone collisions
                for (int j = 0; j < maxStones; j++) {
                    if (stones[j].active && CheckCollision(bullets[i].x, bullets[i].y, stones[j].x, stones[j].y, bulletRadius, stoneSize)) {
                        bullets[i].active = stones[j].active = false;
                        score--; // Decrease score for hitting a stone
                        PlaySound(stoneHitSound);
                    }
                }
            }
        }

        // Check if target score reached and displaying the message and reset if user chooses to retry
        if (score >= targetScore) {
            DisplayEndGameScreen(playAgain, true);
            if (playAgain) {
                ResetGameVariables(player, score, levelTimer, difficultyChosen);
            }
            continue;
        }

        // Update timer
        levelTimer -= GetFrameTime()   ;
        if (levelTimer <= 0) {
            //display the message
            DisplayEndGameScreen(playAgain, false);
            if (!playAgain) break;

            // Reset if user chooses to retry
            ResetGameVariables(player, score, levelTimer, difficultyChosen);
            continue;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(GRAY);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw player
        DrawRectangleRec(player, RED);

        // Draw bullets
        for (int i = 0; i < maxBullets; i++) {
            if (bullets[i].active) DrawCircle(bullets[i].x, bullets[i].y, bulletRadius, RED);
        }

        // Draw targets
        for (int i = 0; i < maxObjects; i++) {
            if (targets[i].active) DrawRectangle(targets[i].x, targets[i].y, objectSize, objectSize, GREEN);
        }

        // Draw stones
        for (int i = 0; i < maxStones; i++) {
            if (stones[i].active) DrawRectangle(stones[i].x, stones[i].y, stoneSize, stoneSize, GRAY);
        }

        // Display score and timer
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Timer: %.1f", levelTimer), 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Target: %d", targetScore), 10, 70, 20, DARKGRAY);

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(background); // Unload background texture and other things 
    UnloadSound(shootSound);
    UnloadSound(hitTargetSound);
    UnloadSound(stoneHitSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}






// ......FUNCTION DEFINITIONS......

void SpawnObject(Object& obj, int screenWidth, int objectSize) {
    obj.x = rand() % (screenWidth - objectSize);
    obj.y = -30; // Spawn above the screen
    obj.active = true;
}

void UpdateObject(Object& obj, float speed) {
    if (obj.active) {
        obj.y += speed;
        if (obj.y > screenHeight) obj.active = false; // Deactivate if off-screen
    }
}

bool CheckCollision(float bx, float by, float ox, float oy, float bradius, float osize) {
    return (bx + bradius > ox && bx - bradius < ox + osize &&
        by + bradius > oy && by - bradius < oy + osize);
}

Difficulty GetDifficulty(float& objectSpeed, float& stoneSpeed, int& targetScore, int& maxActiveStones) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("Choose Difficulty:", screenWidth / 2 - 100, screenHeight / 2 - 80, 30, BLACK);
        DrawText("Press 1 for EASY", screenWidth / 2 - 100, screenHeight / 2 - 30, 20, GREEN);
        DrawText("Press 2 for MEDIUM", screenWidth / 2 - 100, screenHeight / 2, 20, ORANGE);
        DrawText("Press 3 for HARD", screenWidth / 2 - 100, screenHeight / 2 + 30, 20, RED);
        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            objectSpeed = 2.0;
            stoneSpeed = 1.0;
            targetScore = 10;
            maxActiveStones = 3;
            return EASY;
        }
        if (IsKeyPressed(KEY_TWO)) {
            objectSpeed = 3.0;
            stoneSpeed = 2.0;
            targetScore = 20;
            maxActiveStones = 5;
            return MEDIUM;
        }
        if (IsKeyPressed(KEY_THREE)) {
            objectSpeed = 4.0;
            stoneSpeed = 3.0;
            targetScore = 30;
            maxActiveStones = 7;
            return HARD;
        }
    }
    return EASY; // Default fallback
}

void InitializeObjects(Object objects[], int size) {
    for (int i = 0; i < size; i++) {
        objects[i].active = false;
    }
}

void ResetGameVariables(Rectangle& player, int& score, float& levelTimer, bool& difficultyChosen) {
    player.x = screenWidth / 2.0 - playerWidth / 2.0;
    player.y = screenHeight - 70;

    score = 0;
    levelTimer = gameTimer;
    difficultyChosen = false;
}

void DisplayEndGameScreen(bool& playAgain, bool won) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        if (won) {
            DrawText("CONGRATULATIONS! YOU WON!", screenWidth / 2 - 200, screenHeight / 2 - 50, 30, GREEN);
        }
        else {
            DrawText("TIME'S UP! GAME OVER", screenWidth / 2 - 180, screenHeight / 2 - 50, 30, RED);
        }

        DrawText("Press R to Retry or Q to Quit", screenWidth / 2 - 150, screenHeight / 2 + 30, 20, YELLOW);
        EndDrawing();

        if (IsKeyPressed(KEY_R)) {
            playAgain = true;
            return;
        }
        if (IsKeyPressed(KEY_Q)) {
            playAgain = false;
            return;
        }
    }
}
