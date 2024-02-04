#pragma once
#include "raylib.h"
#include <cstdint>

struct AnimationData
{
    Texture2D sheet;
    uint32_t total_frames;
    Rectangle rect;
    uint32_t fps;
};


class AnimationComponent {
private:
    double time_acc;
    double cached_duration;

public:
    uint32_t frame_counter;
    struct AnimationData current_anim;

    void update(double dt, double alpha);
    void reset(const struct AnimationData data);
    Texture2D get_texture() const { return current_anim.sheet; }
    Rectangle get_framerect() const;
};
