#include "System.hpp"
#include <iostream>

int main() {
    int N = 500;           // Number of particles
    double box_size = 1.0; // Size of the simulation box
    double dt = 0.01;      // Time step
    double total_time = 5.0;

    System sys(N, box_size);

    int steps = static_cast<int>(total_time / dt);
    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        sys.step(dt);
        if (i % 50 == 0) // Record every 50 steps
            sys.recordEntropy(t);
    }

    sys.saveCSV("output/entropy_vs_time.csv");
    std::cout << "Simulation finished.\n";
    return 0;
}
