#include "animation.h"
#include <iostream>
#include <format>

void
AnimationComponent::update(double dt, double alpha)
{
    time_acc += dt;
    frame_counter = (time_acc/cached_duration)*current_anim.total_frames;
    if(time_acc >= cached_duration) { time_acc = 0; }
}

void
AnimationComponent::reset(const struct AnimationData data)
{
    current_anim = data;
    cached_duration = data.total_frames/static_cast<double>(data.fps);
    time_acc = 0;
}

Rectangle
AnimationComponent::get_framerect() const
{
    return {current_anim.rect.width * frame_counter,
            0,
            current_anim.rect.width,
            current_anim.rect.height
    };
}