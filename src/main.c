#include <raylib.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "world.h"
#include "stats.h"

static const int screen_width = 800;
static const int screen_height = 800;
static const double fixed_step = 1.0/60.0;

int main(void)
{
    ChangeDirectory(GetApplicationDirectory());
    InitWindow(screen_width, screen_height, "Test");
    
    Font statsFont = LoadFont("assets/RobotoMono-Regular.ttf");

    double physics_time = 0;
    size_t physics_frame_counter = 0;
    size_t render_frame_counter = 0;
    init_world();

    double acc = 0.0;
    while(!WindowShouldClose())
    {
        double frame_time = (double)GetFrameTime(); //TODO: Raylib gives this as a float for some reason, having it as a double
        update_stats(physics_frame_counter, render_frame_counter, physics_time, frame_time);

        acc += frame_time;
        while (acc >= fixed_step)
        {
            physics_tick(physics_time, fixed_step);
            acc -= fixed_step;
            physics_time += fixed_step;
            physics_frame_counter++;

//            printf("%05d | %05d - W PRESSED {%d}\n", physics_frame_counter, render_frame_counter, IsKeyDown(KEY_W));
        }
        const double alpha = acc / fixed_step;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            render_tick(frame_time, alpha);
            render_frame_counter++;
            
            draw_stats(statsFont, 20, 20);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}