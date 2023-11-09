#include "tsp_genetic_algorithm.hpp"
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

GeneticAlgorithm::GeneticAlgorithm(const std::vector<std::vector<double>>& cityGraph, int numberOfCities)
    : cityGraph_(cityGraph), numberOfCities_(numberOfCities), populationSize(numberOfCities*10), numGenerations(numberOfCities*100), crossoverRate(0.8), mutationRate(0.2) {}

void GeneticAlgorithm::populate(){
    srand(static_cast<unsigned>(time(nullptr)));

    for(int i = 0; i < populationSize; i++){
        std::vector<int> tour(numberOfCities_);
        for (int j = 0; j < numberOfCities_; j++) {
            tour[j] = j;
        }

        // Shuffle the tour to create a random permutation
        for (int j = numberOfCities_ - 1; j > 0; --j) {
            int randIndex = rand() % (j + 1);
            std::swap(tour[j], tour[randIndex]);
        }
        population.push_back(tour);
    }
}

double GeneticAlgorithm::computeTourDistance(const std::vector<int>& tour){
    double distance = 0.0;
    for (int i = 0; i < numberOfCities_ - 1; ++i) {
        distance += cityGraph_[tour[i]][tour[i + 1]];
    }
    distance += cityGraph_[tour[numberOfCities_ - 1]][tour[0]]; // Return to the starting city
    return distance;
}

const std::vector<int>& GeneticAlgorithm::getBestTour() const{
    return bestTour_;
}

void GeneticAlgorithm::selectParents(std::vector<int>& parent1, std::vector<int>& parent2){
    std::vector<std::vector<int>> tournament;
    int tournamentSize = populationSize;

    for (int i = 0; i < tournamentSize; i++) {
        int index = rand() % population.size();
        tournament.push_back(population[index]);
    }

    std::vector<int> bestIndividual1 = tournament[0];
    std::vector<int> bestIndividual2 = tournament[1];

    for(int i = 0; i < tournamentSize; i++){
        if(computeTourDistance(tournament[i]) < computeTourDistance(bestIndividual1)){
            std::vector<int> temp = bestIndividual1;
            bestIndividual1 = tournament[i];
            bestIndividual2 = temp;
        }
        else if(computeTourDistance(tournament[i]) < computeTourDistance(bestIndividual2)){
            bestIndividual2 = tournament[i];
        }
    }

    parent1 = bestIndividual1;
    parent2 = bestIndividual2;
}

std::vector<int> GeneticAlgorithm::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2, std::vector<int>& offspring1, std::vector<int>& offspring2) {
    int tourSize = parent1.size();

    // Randomly select a segment
    std::uniform_int_distribution<int> dist(0, tourSize - 1);
    int startPos = dist(rng);
    int endPos = dist(rng);

    if (startPos > endPos) {
        std::swap(startPos, endPos);
    }

    offspring1.assign(tourSize, -1);
    offspring2.assign(tourSize, -1);

    // Copy the segment from parent1 to child1 and parent2 to child2
    for (int i = startPos; i <= endPos; ++i) {
        offspring1[i] = parent1[i];
        offspring2[i] = parent2[i];
    }

    int index1 = endPos + 1;
    int index2 = endPos + 1;

    for (int i = 0; i < tourSize; ++i) {
        if (i >= startPos && i <= endPos) {
            continue; 
        }

        // Fill child1 with the order from parent2
        while (std::find(offspring1.begin(), offspring1.end(), parent2[index1 % tourSize]) != offspring1.end()) {
            index1++;
        }
        offspring1[i] = parent2[index1 % tourSize];

        // Fill child2 with the order from parent1
        while (std::find(offspring2.begin(), offspring2.end(), parent1[index2 % tourSize]) != offspring2.end()) {
            index2++;
        }
        offspring2[i] = parent1[index2 % tourSize];

        index1++;
        index2++;
    }
}

void GeneticAlgorithm::mutate(std::vector<int>& individual) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    int individualSize = individual.size();

    for (int& gene : individual) {
        if (dist(rng) < mutationRate) {  
            int j = gene;
            while (j == gene) {
                j = rand() % individualSize; 
            }
            std::swap(gene, individual[j]); 
        }
    }
}

double GeneticAlgorithm::computeShortestTour(){
    populate();

    for(int numGen = 0; numGen < numGenerations; numGen++){
        std::vector<std::vector<int>> newPopulation;

        for (int i = 0; i < populationSize / 2; ++i) {
            std::vector<int> parent1, parent2;
            selectParents(parent1, parent2);

            if (std::uniform_real_distribution<>(0.0, 1.0)(rng) < crossoverRate) {
                std::vector<int> offspring1, offspring2;
                crossover(parent1, parent2, offspring1, offspring2);

                mutate(offspring1);  
                mutate(offspring2); 

                newPopulation.push_back(offspring1);
                newPopulation.push_back(offspring2);
            } else {
                // No crossover
                newPopulation.push_back(parent1);
                newPopulation.push_back(parent2);
            }
        }
        population = newPopulation;
    }

    double shortestDistance = std::numeric_limits<double>::max();
    for(int i = 0; i < population.size(); i++){
        double currentDistance = computeTourDistance(population[i]);
        if(currentDistance < shortestDistance){
            shortestDistance = currentDistance;
            bestTour_ = population[i];
        }
    }
    return shortestDistance;
}
