#pragma once
#include <vector>
#include <cmath>

inline double computeEntropyFromDistribution(const std::vector<int>& counts, int total) {
    const double kB = 1.0; 
    double S = 0.0;
    for (int c : counts) {
        if (c == 0) continue;
        double p = static_cast<double>(c) / total;
        S -= p * std::log(p);
    }
    return kB * S;
}
