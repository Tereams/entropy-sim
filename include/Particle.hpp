#pragma once
#include <cmath>

struct Particle {
    double x, y;    // position
    double vx, vy;  // speed

    Particle(double x_, double y_, double vx_, double vy_)
        : x(x_), y(y_), vx(vx_), vy(vy_) {}

    void update(double dt, double box_size) {
        x += vx * dt;
        y += vy * dt;
        // Bounce back at the boundary
        if (x < 0) { x = -x; vx = -vx; }
        if (x > box_size) { x = 2*box_size - x; vx = -vx; }
        if (y < 0) { y = -y; vy = -vy; }
        if (y > box_size) { y = 2*box_size - y; vy = -vy; }
    }

    double speed() const { return std::sqrt(vx*vx + vy*vy); }
};
