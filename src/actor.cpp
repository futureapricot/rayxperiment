#include "actor.h"
#include "animation.h"
#include "raylib.h"
#include <limits>
#include <cstdlib>
#include <algorithm>


void
Actor::phys_update(double dt)
{
    transform.update();
}

void
Actor::render_update(double dt, double alpha)
{
    render.update(transform, alpha);
}

void
Actor::draw()
{
    render.draw();
}

void
Player::render_update(double dt, double alpha)
{
    anim.update(dt, alpha);
    
    if(transform.has_epsilon_positive()) {
        if (currentAnimState == AnimState::idle){
            currentAnimState = AnimState::walking;
            anim.reset(walkAnim);
        }
    } else {
        if (currentAnimState == AnimState::walking){
            currentAnimState = AnimState::idle;
            anim.reset(idleAnim);
        }  
    }

    render.texture = anim.get_texture();
    render.rect = anim.get_framerect();
    Actor::render_update(dt, alpha);
}

void
PlayerRed::phys_update(double dt)
{
    Player::phys_update(dt);
    constexpr int speed = 200;

    if(IsKeyDown(KEY_W)) {
        transform.position.y -= dt*speed;
    }
    if(IsKeyDown(KEY_A)) {
        transform.position.x -= dt*speed;
    }
    if(IsKeyDown(KEY_S)) {
        transform.position.y += dt*speed;
    }
    if(IsKeyDown(KEY_D)) {
        transform.position.x += dt*speed;
    }
}

void
PlayerBlue::phys_update(double dt)
{
    Player::phys_update(dt);
    constexpr int speed = 200;

    if(IsKeyDown(KEY_UP)) {
        transform.position.y -= dt*speed;
    }
    if(IsKeyDown(KEY_LEFT)) {
        transform.position.x -= dt*speed;
    }
    if(IsKeyDown(KEY_DOWN)) {
        transform.position.y += dt*speed;
    }
    if(IsKeyDown(KEY_RIGHT)) {
        transform.position.x += dt*speed;
    }
}

void
WorldTransformComponent::update()
{
    position_prev = position;
}

Vector2
WorldTransformComponent::epsilon() const
{
    return {position.x-position_prev.x, position.y-position_prev.y};
}

bool
WorldTransformComponent::has_epsilon_positive() const
{
    using namespace std;
    auto e = epsilon();
    return abs(e.x) >= numeric_limits<double>::epsilon() 
        || abs(e.y) >= numeric_limits<double>::epsilon();
}

Vector2
WorldTransformComponent::lerp(double alpha) const
{
    alpha = std::clamp(alpha, 0.0, 1.0);
    return {
        static_cast<float>((1.0-alpha)*position_prev.x + (alpha * position.x)),
        static_cast<float>((1.0-alpha)*position_prev.y + (alpha * position.y))
    };
}

void
RenderComponent::draw() const
{
    DrawTextureRec(
        texture,
        rect,
        position,
        WHITE);
}

void
RenderComponent::update(const WorldTransformComponent& transform, double alpha) {
    position = transform.lerp(alpha);
}