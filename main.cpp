#include <iostream>
#include <raylib.h>
#include <cmath>
#include <ctime>
#include <raymath.h>

const int screenWidth = 900;
const int screenHeight = 900;
const int FPS = 60;

Color blue = {0, 0, 255, 255};

class Stars {
    public:
        int number = 100;
        int xpos = 0;
        int ypos = 0;

        int radius = 3;
        
        Vector2 sol[100];

        Stars() {
            for (int i = 0; i < number + 1; i++) {
                xpos = rand() % screenWidth + 1;
                ypos = rand() % screenHeight + 1;
                sol[i].x = xpos;
                sol[i].y = ypos;
            }
        }

        void Draw() {
            for (int i = 0; i < number + 1; i++) {
                DrawCircle(sol[i].x, sol[i].y, radius, WHITE);
            }
        }

        void Update() {
            Draw();
        }
};

class Sun {
    public:
        int radius = 50;
        int xpos = screenWidth / 2;
        int ypos = screenHeight / 2;
        Vector2 pos;

        void Draw() {
            DrawCircle(xpos, ypos, radius, YELLOW);
        }

        void Update() {
            Draw();

            pos.x = xpos;
            pos.y = ypos;
        }
};

class Planet {
    public:
        Vector2 position;
        float speed;
        float radius;
        float distance;
        float theta;
        Color color;

        Planet(float distance, float theta, Sun sun, float speed, int radius, Color color) {
            this->distance = distance;
            this->theta = theta;
            this->position.x = sun.xpos + distance * cos(theta);
            this->position.y = sun.ypos + distance * sin(theta);
            this->speed = speed;
            this->radius = radius;
            this->color = color;
        }

        void Draw() {
            DrawCircle(position.x, position.y, radius, color);
        }

        void Update(Sun sun) {
            theta += speed;
            position.x = sun.xpos + distance * cos(theta);
            position.y = sun.ypos + distance * sin(theta);

            Draw();
        }
};

int main() {
    srand(time(NULL));

    Stars stars;
    Sun sun;
    Planet mercury(80, 0.0, sun, 0.03, 2, GRAY);
    Planet venus(140, 0.0, sun, -0.025, 4, ORANGE);
    Planet earth(200, 0.0, sun, 0.02, 4, blue);
    Planet mars(300, 0.0, sun, -0.015, 2, RED);
    Planet jupiter(350, 0.0, sun, 0.01, 22, ORANGE);
    Planet saturn(400, 0.0, sun, 0.0075, 18, YELLOW);
    Planet uranus(500, 0.0, sun, -0.005, 8, LIGHTGRAY);
    Planet neptune(600, 0.0, sun, -0.0005, 6, BLUE);

    InitWindow(screenWidth, screenHeight, "Solar System Simulator");
    SetTargetFPS(FPS);
    
    while (WindowShouldClose() == false){
        BeginDrawing();

        ClearBackground(BLACK);

        stars.Update();
        sun.Update();
        
        mercury.Update(sun);
        venus.Update(sun);
        earth.Update(sun);
        mars.Update(sun);
        jupiter.Update(sun);
        saturn.Update(sun);
        uranus.Update(sun);
        neptune.Update(sun);

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}