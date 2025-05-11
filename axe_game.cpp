#include "raylib.h"
#include <cstdio>
#include <cmath>

int main()
{
    // window dimensions
    int width = 800;
    int height = 500;
    InitWindow(width, height, "Save the circle");

    // circle coordinates
    int circle_x{250};
    int circle_y{250};
    int circle_radius{50}; // radius of the circle

    // circle edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int t_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    // axe coordinates
    int axe_x{375};
    int axe_y{0};
    int axe_length{50};

    // axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int t_axe_y{axe_y};
    int b_axe_y{axe_y + axe_length};

    int direction{10}; // axe movement
    int score = 0;     // player score
    bool has_crossed_once = false; // track if circle has ever crossed middle
    bool scored = false; // track current crossing state
    const int middle_line = width / 2; // middle of the screen at x=400

    // collision logic
    bool collision_with_axe =
        (b_axe_y >= t_circle_y) &&
        (t_axe_y <= b_circle_y) &&
        (l_axe_x <= r_circle_x) &&
        (r_axe_x >= l_circle_x);

    // Pawn movement
    int movementSpeed_circle = 8;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Try not to touch the square",540,0,20,BLUE);
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, GREEN); // Display score
        
        if (collision_with_axe)
        {
            DrawText("Game Over!", 275, 200, 50, RED);
        }
        else
        {
            // Game logic begins

            // update circle edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            t_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            // update axe edges
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            t_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            // update collision with axe
            collision_with_axe =
                (b_axe_y >= t_circle_y) &&
                (t_axe_y <= b_circle_y) &&
                (l_axe_x <= r_circle_x) &&
                (r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Draw middle line for visual reference (optional)
            DrawLine(middle_line, 0, middle_line, height, GRAY);

            // Score system - check if circle crosses middle line
            if (r_circle_x >= middle_line && l_circle_x <= middle_line)
            {
                if (!scored && has_crossed_once)
                {
                    score += 5;
                    scored = true;
                }
                has_crossed_once = true;
            }
            else
            {
                scored = false;
            }

            axe_y += direction;
            if (axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }

            if (IsKeyDown(KEY_A) && circle_x > 0 + circle_radius)
            {
                circle_x -= movementSpeed_circle;
            }

            if (IsKeyDown(KEY_D) && circle_x < width - circle_radius)
            {
                circle_x += movementSpeed_circle;
            }

            if (IsKeyDown(KEY_W) && circle_y > 0 + circle_radius)
            {
                circle_y -= movementSpeed_circle;
            }

            if (IsKeyDown(KEY_S) && circle_y < 500 - circle_radius)
            {
                circle_y += movementSpeed_circle;
            }
            // Game logic ends
        }

        EndDrawing();
    }
}