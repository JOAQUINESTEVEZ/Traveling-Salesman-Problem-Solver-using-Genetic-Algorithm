#ifndef TSP_GENETIC_ALGORITHM_HPP
#define TSP_GENETIC_ALGORITHM_HPP
#include <vector>
#include <random>

class GeneticAlgorithm{
    private: 
        double computeTourDistance(const std::vector<int>& tour);;
        int numberOfCities_;
        const std::vector<std::vector<double>>& cityGraph_;
        std::vector<int> bestTour_;
        std::vector<std::vector<int>> population;
        int populationSize;
        int numGenerations;
        double crossoverRate;
        double mutationRate;
        std::mt19937 rng;
        void populate();
        void selectParents(std::vector<int>& parent1, std::vector<int>& parent2);
        std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2, std::vector<int>& offspring1, std::vector<int>& offspring2);
        void mutate(std::vector<int>& individual);
    public:
        GeneticAlgorithm(const std::vector<std::vector<double>>& cityGraph, int numberOfCities);
        double computeShortestTour();
        const std::vector<int>& getBestTour() const;
};

#endif    // TSP_GENETIC_ALGORITHM_HPP