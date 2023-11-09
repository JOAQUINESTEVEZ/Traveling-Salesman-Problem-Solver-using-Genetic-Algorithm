#include "tsp_brute_force.hpp"
#include <algorithm>
#include <limits>

using namespace std;

TSPBruteForce::TSPBruteForce(const vector<vector<double>>& cityGraph, int numberOfCities)
    : cityGraph_(cityGraph), numberOfCities_(numberOfCities) {}

double TSPBruteForce::computeShortestTour() {
    vector<int> tour(numberOfCities_);
    for (int i = 0; i < numberOfCities_; ++i) {
        tour[i] = i;
    }

    double shortestDistance = numeric_limits<double>::max();

    do {
        double currentDistance = computeTourDistance(tour);
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            bestTour_ = tour;
        }
    } while (next_permutation(tour.begin(), tour.end()));

    return shortestDistance;
}

double TSPBruteForce::computeTourDistance(const vector<int>& tour) {
    double distance = 0.0;
    for (int i = 0; i < numberOfCities_ - 1; ++i) {
        distance += cityGraph_[tour[i]][tour[i + 1]];
    }
    distance += cityGraph_[tour[numberOfCities_ - 1]][tour[0]]; // Return to the starting city
    return distance;
}

const vector<int>& TSPBruteForce::getBestTour() const {
    return bestTour_;
}
