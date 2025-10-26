#include "System.hpp"
#include "Entropy.hpp"
#include <random>
#include <fstream>
#include <iostream>

System::System(int n_particles, double box_size_) : box_size(box_size_) {
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> pos(0.0, box_size);
    std::normal_distribution<double> vel_fast(0.0, 2.0); // high temperature
    std::normal_distribution<double> vel_slow(0.0, 0.5); // low temperature

    for (int i = 0; i < n_particles; ++i) {
        double x = (i < n_particles/2) ? pos(gen) * 0.5 : 0.5*box_size + pos(gen)*0.5;
        double y = pos(gen);
        auto& vdist = (i < n_particles/2) ? vel_fast : vel_slow;
        double vx = vdist(gen);
        double vy = vdist(gen);
        particles.emplace_back(x, y, vx, vy);
    }
}

void System::step(double dt) {
    for (auto& p : particles) {
        p.update(dt, box_size);
    }
}

double System::computeEntropy(int n_bins) {
    std::vector<int> bins(n_bins, 0);
    double max_v = 0.0;
    for (auto& p : particles) max_v = std::max(max_v, p.speed());
    if (max_v == 0) return 0.0;

    for (auto& p : particles) {
        int idx = std::min((int)(p.speed() / max_v * (n_bins-1)), n_bins-1);
        bins[idx]++;
    }

    return computeEntropyFromDistribution(bins, particles.size());
}

void System::recordEntropy(double time) {
    double S = computeEntropy();
    entropy_log.emplace_back(time, S);
    std::cout << "t=" << time << ", S=" << S << "\n";
}

void System::saveCSV(const std::string& filename) const {
    std::ofstream ofs(filename);
    ofs << "time,entropy\n";
    for (auto& [t, S] : entropy_log) {
        ofs << t << "," << S << "\n";
    }
    ofs.close();
}
