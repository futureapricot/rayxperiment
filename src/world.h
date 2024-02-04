#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void init_world(void);
void physics_tick(double t, double dt);
void render_tick(double dt, double alpha);

#ifdef __cplusplus
}
#endif