#pragma once
#include <vector>
#include "Particle.hpp"

class System {
public:
    System(int n_particles, double box_size);
    void step(double dt);
    void recordEntropy(double time);
    void saveCSV(const std::string& filename) const;

private:
    std::vector<Particle> particles;
    std::vector<std::pair<double,double>> entropy_log; // (time, S)
    double box_size;

    double computeEntropy(int n_bins = 50);
};
