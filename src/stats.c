#include "stats.h"
#include "raylib.h"
#include "math.h"

static size_t physics_frame_counter = 0;
static size_t render_frame_counter = 0;
static double physics_time = 0;
static double delta_time = 0;

#define FPS_WINDOW 1000
int fps_idx;
int fps_window[FPS_WINDOW];
int fps_rolling;

void update_stats(size_t ph_fc, size_t rd_fc, double ph_time, double dt)
{
    physics_frame_counter = ph_fc;
    render_frame_counter = rd_fc;
    physics_time = ph_time;
    delta_time = dt;

    fps_window[fps_idx] = (int)round(1.0/dt);
    fps_idx = (fps_idx + 1)%FPS_WINDOW;
    if(render_frame_counter >= FPS_WINDOW) {
        for (size_t i = 0; i < FPS_WINDOW; i++) {
            fps_rolling += fps_window[i];
        }
        fps_rolling = round((double)fps_rolling/(double)FPS_WINDOW);
    }
}

void draw_stats(Font f, int ox, int oy)
{
    const int h = 20;
    //////////////////////////////////////
    double RealTime = GetTime();
    DrawTextEx(f, TextFormat("RAYLIB  TIME: %018.7f", RealTime)   , (Vector2){ ox, oy       }, h, 1, BLACK);
    DrawTextEx(f, TextFormat("PHYSICS TIME: %018.7f", physics_time), (Vector2){ ox, oy + 1*h }, h, 1, ORANGE);
    DrawTextEx(f, TextFormat("       EPSILON [ms]: %04.5f", (RealTime-physics_time)*1000), (Vector2){ ox, oy + 2*h }, h, 1, GREEN);
    /////////////////////////////////////
    DrawTextEx(f, TextFormat("PHYSICS FrameCount: %010d", physics_frame_counter), (Vector2){ ox, oy + 4*h}, h, 1, ORANGE);
    DrawTextEx(f, TextFormat("RENDER  FrameCount: %010d", render_frame_counter ), (Vector2){ ox, oy + 5*h}, h, 1, PURPLE);
    DrawTextEx(f, TextFormat("           EPSILON: %010d", render_frame_counter-physics_frame_counter ), (Vector2){ ox, oy + 6*h}, h, 1, GREEN);
    ////////////////////////////////////
    DrawTextEx(f, TextFormat("RENDER DeltaTime  [s]: %.8f", delta_time), (Vector2){ ox, oy + 8*h}, h, 1, PURPLE);
    DrawTextEx(f, TextFormat("RENDER DeltaTime [ms]: %.4f", delta_time*1000), (Vector2){ ox, oy + 9*h}, h, 1, BLUE);
    DrawTextEx(f, TextFormat("RENDER            FPS: %.2f", 1.0/delta_time ), (Vector2){ ox, oy + 10*h}, h, 1, RED);
    DrawTextEx(f, TextFormat("RENDER         MA FPS: %05d", fps_rolling), (Vector2){ ox, oy + 11*h}, h, 1, PINK);
}