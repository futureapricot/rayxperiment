#include "world.h"
#include "raylib.h"
#include <iostream>
#include <format>

#include "actor.h"
#include <memory>

static std::unique_ptr<Actor> Actor0;
static std::unique_ptr<Actor> Actor1;

void init_world(void)
{
    struct AnimationData IdleAnim { LoadTexture("assets/idle.png"), 11, Rectangle(0,0,800,800), 12 };
    struct AnimationData WalkAnim { LoadTexture("assets/walk.png"), 12, Rectangle(0,0,800,800), 12 };

    Actor0.reset(new PlayerRed(Vector2{-400, 0}, IdleAnim, WalkAnim));
    Actor1.reset(new PlayerBlue(Vector2{0, 0}, IdleAnim, WalkAnim));
}

void physics_tick(double t, double dt)
{
//    std::cout << std::format("PHY press {}\tdown {}\treleased {}\tup {}\n",
//        IsKeyPressed(KEY_W),
//        IsKeyDown(KEY_W),
//        IsKeyReleased(KEY_W),
//        IsKeyUp(KEY_W));

    Actor0->phys_update(dt);
    Actor1->phys_update(dt);
}

void render_tick(double dt, double alpha)
{
//    std::cout << std::format("REN press {}\tdown {}\treleased {}\tup {}\n",
//        IsKeyPressed(KEY_W),
//        IsKeyDown(KEY_W),
//        IsKeyReleased(KEY_W),
//        IsKeyUp(KEY_W));

    Actor0->render_update(dt, alpha);
    Actor1->render_update(dt, alpha);

    Actor0->draw();
    Actor1->draw();
}