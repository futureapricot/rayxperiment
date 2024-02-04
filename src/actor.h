#pragma once
#include "raylib.h"
#include "animation.h"
#include <cstdint>
#include <iostream>
#include <format>
#include <limits>


class WorldTransformComponent {
private:
    Vector2 position_prev;
public:
    Vector2 position;

    WorldTransformComponent(Vector2 p)
        : position(p), position_prev(p)
    {}
    void update();
    Vector2 epsilon() const;
    bool has_epsilon_positive() const;
    Vector2 lerp(double alpha) const;
};

class RenderComponent {
public:
    Vector2 position;
    Texture2D texture;
    Rectangle rect;

    void update(const WorldTransformComponent& transform, double alpha);
    void draw() const;
};


class Actor {
public:
    Actor(Vector2 pos)
        : transform({pos})
    {}

    WorldTransformComponent transform;
    RenderComponent render;

    virtual void phys_update(double dt);
    virtual void render_update(double dt, double alpha);
    virtual void draw();
};


class Player : public Actor {
private:
    const AnimationData idleAnim;
    const AnimationData walkAnim;
    enum class AnimState { idle, walking };
    AnimState currentAnimState;
public:
    Player(Vector2 pos, const AnimationData idleAnim, const AnimationData walkAnim)
        : Actor(pos), idleAnim(idleAnim), walkAnim(walkAnim)
    {
        anim.reset(idleAnim);
    }
    AnimationComponent anim;
    void render_update(double dt, double alpha) override;
};


class PlayerRed : public Player {
public:
    PlayerRed(Vector2 pos, AnimationData idleAnim, AnimationData walkAnim)
        : Player(pos, idleAnim, walkAnim)
    {}

    void phys_update(double dt) override;
};


class PlayerBlue : public Player {
public:
    PlayerBlue(Vector2 pos, AnimationData idleAnim, AnimationData walkAnim)
        : Player(pos, idleAnim, walkAnim)
    {}

    void phys_update(double dt) override;
};