#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tsp_brute_force.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input_file> <number_of_cities>" << endl;
    return 1;
  }

  string inputFileName = argv[1];
  int numberOfCities = stoi(argv[2]);

  if (numberOfCities > 20 || numberOfCities <= 0) {
    cerr << "Number of cities should be between 1 and 20." << endl;
    return 1;
  }

  ifstream inputFile(inputFileName);
  if (!inputFile.is_open()) {
    cerr << "Failed to open the input file." << endl;
    return 1;
  }

  vector<vector<double>> cityGraph(20, vector<double>(20, 0.0));
  string line;
  int rowIndex = 0;

  while (getline(inputFile, line) && rowIndex < 20) {
    stringstream ss(line);
    string value;
    int colIndex = 0;

    while (getline(ss, value, ',') && colIndex < 20) {
      cityGraph[rowIndex][colIndex] = stod(value);
      colIndex++;
    }

    rowIndex++;
  }
  inputFile.close();

  // Brute Force
  TSPBruteForce bruteForce(cityGraph, numberOfCities);
  auto start = chrono::high_resolution_clock::now();
  double bruteForceResult = bruteForce.computeShortestTour();
  auto end = chrono::high_resolution_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - start).count();
  cout << "Brute Force Best Tour: " << bruteForceResult << " Time: " << duration
       << "ms" << endl;
  cout << "Best Tour: ";
  for (int city : bruteForce.getBestTour()) {
    cout << city << " ";
  }
  cout << endl;

  return 0;
}
