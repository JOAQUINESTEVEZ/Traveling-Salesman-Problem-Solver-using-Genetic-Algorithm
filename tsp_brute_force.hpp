#ifndef TSP_BRUTE_FORCE_HPP
#define TSP_BRUTE_FORCE_HPP

#include <vector>

class TSPBruteForce {
public:
    TSPBruteForce(const std::vector<std::vector<double>>& cityGraph, int numberOfCities);

    double computeShortestTour();
    const std::vector<int>& getBestTour() const;

private:
    const std::vector<std::vector<double>>& cityGraph_;
    int numberOfCities_;
    std::vector<int> bestTour_;
    double computeTourDistance(const std::vector<int>& tour);
};

#endif // TSP_BRUTE_FORCE_HPP
