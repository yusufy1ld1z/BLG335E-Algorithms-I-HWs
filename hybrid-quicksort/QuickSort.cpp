/**
  BLG335E - Analysis of Algorithms I - Project 1
  Author: Yusuf Yıldız
  Student ID: 150210006
  Date: 25.11.2023
*/

/**
 * @file QuickSort.cpp
 * @brief This file contains the implementation of the QuickSort algorithm.
 */
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <chrono>

/**
 * @brief Represents a population data structure for sorting.
 */
struct Population {
  Population(std::string city, int population) : city(city), population(population) {}
  std::string city; ///< City name (city;population) is taken as whole for simplicity
  int population;   ///< Population count
};

/**
 * @brief Represents a logger entry for logging purposes.
 */
struct Logger{ // created for logging
  Logger(int pivot, std::string array) : pivot(pivot), array(array) {}
  int pivot;          ///< Pivot value
  std::string array;  ///< String representation of an array
};

std::vector<Logger> logger; // global logger vector

// int COMPARISON_COUNT = 0; // global comparison count

// Utility functions

/**
 * @brief Converts a vector of Population to a string.
 * @param vec The vector to be converted.
 * @return The string representation of the vector.
 */
std::string vectorToString(std::vector<Population> vec);

/**
 * @brief Swaps two elements in a vector.
 * @param vec The vector containing elements to be swapped.
 * @param i1 Index of the first element.
 * @param i2 Index of the second element.
 */
void quickSwap(std::vector<Population> &vec, int i1, int i2);

/**
 * @brief Validates command line arguments.
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return True if arguments are valid, otherwise false.
 */
bool validateArguments(int argc, char **argv);

// Sorting functions

/**
 * Sorts a vector using the naive QuickSort algorithm.

 * The naive QuickSort algorithm uses the last element as the pivot when threshold is given as 1..

 * @param vec The vector to be sorted.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 * @param pivotType Type of pivot selection strategy ('l' for last, 'r' for random, 'm' for median of three).
 * @param verbose If true, log the sorting process.
 */
void naiveQuickSort(std::vector<Population> &vec, int head, int tail, char pivotType, bool verbose);

/**
 * @brief Sorts a vector using the hybrid QuickSort algorithm.

 * The hybrid QuickSort algorithm determines the pivot by pivotType and then recursively call itself 
 * until the subarray size is lower of equals to the threshold, if so, sort the array using insertionSort.

 * @param vec The vector to be sorted.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 * @param threshold Threshold for switching to insertion sort.
 * @param pivotType Type of pivot selection strategy ('l' for last, 'r' for random, 'm' for median of three).
 * @param verbose If true, log the sorting process.
 */
void hybridQuickSort(std::vector<Population> &vec, int head, int tail, int threshold, char pivotType, bool verbose);

// IO functions

/**
 * @brief Reads population data from a CSV file.
 * @param fileName The name of the CSV file.
 * @param vec The vector to store the population data.
 */
void readFromCsv(const std::string fileName, std::vector<Population> &vec);

/**
 * @brief Writes population data to a CSV file.
 * @param fileName The name of the CSV file.
 * @param vec The vector containing population data.
 */
void writeToCsv(const std::string fileName, const std::vector<Population> &vec);

/**
 * @brief Writes logger data to a file.
 * @param fileName The name of the file.
 * @param vec The vector containing logger data.
 */
void writeLogger(const std::string fileName, const std::vector<Logger> &vec);

/**
 * @brief The main function that orchestrates the sorting process based on command line arguments.
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return 0 if successful, 1 otherwise.
 */
int main(int argc, char **argv) {
  std::srand(std::time(nullptr)); // seed for random number generator

  std::string input_file_name;
  std::string output_file_name;
  char pivot_strategy;
  int threshold;
  bool verbose;

  if(!validateArguments(argc, argv)) { // validate command line arguments
    return 1;
  }else{
    input_file_name = argv[1];
    pivot_strategy = argv[2][0];
    threshold = std::stoi(argv[3]);
    output_file_name = argv[4];
    if(argc == 6){ // if verbose is given
      verbose = true;   
    } else{
      verbose = false;
    }
  }

  std::vector<Population> population_data; // created for population data

  readFromCsv(input_file_name, population_data); // read from csv

  if(threshold == 1){ // if threshold is 1, use naive quicksort
    auto start = std::chrono::high_resolution_clock::now();
    naiveQuickSort(population_data, 0, population_data.size() - 1, pivot_strategy, verbose);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // in nanoseconds
    std::cout << "Time taken by QuickSort with pivot strategy \'" << std::string(1, pivot_strategy) // print the output in desired format
              << "\' and threshold " << threshold << ": " << duration.count() << " ns." << std::endl;
  } else{ // otherwise use hybrid quicksort
    auto start = std::chrono::high_resolution_clock::now();
    hybridQuickSort(population_data, 0, population_data.size() - 1, threshold, pivot_strategy, verbose);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // in nanoseconds
    std::cout << "Time taken by QuickSort with pivot strategy \'" << std::string(1, pivot_strategy) // print the output in desired format
              << "\' and threshold " << threshold << ": " << duration.count() << " ns." << std::endl;
  }

  writeToCsv(output_file_name, population_data); // write to csv

  if(verbose){
    writeLogger("log.txt", ::logger); // write logger to file if verbose is given
  }

  // std::cout << "Total comparison made by quicksort : " << COMPARISON_COUNT << std::endl; // print the total comparison count
  return 0;
}

// Sorting functions

/**
 * @brief Sorts a vector using the insertion sort algorithm.

 * The insertion sort algorithm sorts the vector in place when threshold condition is satisfied in hybridQuickSort.

 * @param vec The vector to be sorted.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 */
void insertionSort(std::vector<Population> &vec, int head, int tail) {
  for (int i = head + 1; i <= tail; i++) {
    Population key = vec[i];
    int j = i - 1;
    while (j >= 0 && vec[j].population > key.population) {
      vec[j + 1] = vec[j];
      j--;
    }
    vec[j + 1] = key;
  }
}

/**
 * @brief Partitions the vector using the last element as the pivot.

 * Base partition function for all pivot selection strategies, determines the last element as pivot.
 * If verbose is true, then logs the partitioning process.

 * @param vec The vector to be partitioned.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 * @param verbose If true, log the partitioning process.
 * @return The index of the pivot after partitioning.
 */
int lastPartition(std::vector<Population> &vec, int head, int tail, bool verbose){
  Population pivot = vec[tail]; // last element as pivot
  int i = head;
  for(int j = head; j <= tail; j++) {
    if(vec[j].population < pivot.population){
      quickSwap(vec, i, j);
      i++;
    }
  }
  // COMPARISON_COUNT+=2 * (tail - head + 1) + 1; // total comparison by if and for blocks
  quickSwap(vec, i, tail);
  if(verbose) {
    auto start = vec.begin() + head;
    auto end = vec.begin() + tail + 1;
    ::logger.push_back(Logger(vec[i].population, vectorToString(std::vector<Population>(start, end)))); // log the partitioning process
  }
  return i;
}

/**
 * @brief Partitions the vector using a random element as the pivot.

 * Randomly chooses an element as the pivot and swaps it with the last element, then calls lastPartition.

 * @param vec The vector to be partitioned.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 * @param verbose If true, log the partitioning process.
 * @return The index of the pivot after partitioning.
 */
int randomPartition(std::vector<Population> &vec, int head, int tail, bool verbose){
  int pivot = rand() % (tail - head + 1) + head; // random pivot
  quickSwap(vec, pivot, tail); // swap pivot with last element
  return lastPartition(vec, head, tail, verbose); // partition with last element as pivot
}

/**
 * @brief Partitions the vector using the median of three random elements as the pivot.

 * Randomly chooses three index then find the median element's index and swaps the median with the last element, then calls lastPartition.

 * @param vec The vector to be partitioned.
 * @param head Index of the head of the vector.
 * @param tail Index of the tail of the vector.
 * @param verbose If true, log the partitioning process.
 * @return The index of the pivot after partitioning.
 */
int median3Partition(std::vector<Population> &vec, int head, int tail, bool verbose){
  int pivot1 = rand() % (tail - head + 1) + head;
  int pivot2 = rand() % (tail - head + 1) + head;
  int pivot3 = rand() % (tail - head + 1) + head;
  int median;

  if(vec[pivot1].population <= vec[pivot2].population && vec[pivot1].population >= vec[pivot3].population) {median = pivot1;} 
  else if(vec[pivot2].population <= vec[pivot1].population && vec[pivot2].population >= vec[pivot3].population) {median = pivot2;}  // find median of three random elements
  else {median = pivot3;}
  // COMPARISON_COUNT+=4; // total comparison by if blocks

  quickSwap(vec, median, tail); // swap median with last element
  return lastPartition(vec, head, tail, verbose); // partition with last element as pivot
}

void naiveQuickSort(std::vector<Population> &vec, int head, int tail, char pivotType, bool verbose) {
  if(head < tail) {
    int pivot;
    switch(pivotType) {
      case 'l':
        pivot = lastPartition(vec, head, tail, verbose); // last element as pivot
        break;
      case 'r': 
        pivot = randomPartition(vec, head, tail, verbose); // random element as pivot
        break;
      case 'm':
        pivot = median3Partition(vec, head, tail, verbose); // median of three random elements as pivot
        break;
    }
    naiveQuickSort(vec, head, pivot - 1, pivotType, verbose);
    naiveQuickSort(vec, pivot + 1, tail, pivotType, verbose);
  }
  // COMPARISON_COUNT+=4; // total comparison by if and switch blocks
}

void hybridQuickSort(std::vector<Population> &vec, int head, int tail, int threshold, char pivotType, bool verbose) {
  if(head < tail) {
    int pivot;
    if(tail - head + 1 <= threshold) { // if size of the vector is less than or equal to threshold, use insertion sort
      insertionSort(vec, head, tail);
    }
    else { // otherwise use hybrid quicksort
      switch(pivotType) {
        case 'l':
          pivot = lastPartition(vec, head, tail, verbose); // last element as pivot
          break;
        case 'r': 
          pivot = randomPartition(vec, head, tail, verbose); // random element as pivot
          break;
        case 'm':
          pivot = median3Partition(vec, head, tail, verbose); // median of three random elements as pivot
          break;
      }
      hybridQuickSort(vec, head, pivot - 1, threshold, pivotType, verbose);
      hybridQuickSort(vec, pivot + 1, tail, threshold, pivotType, verbose);
    }
  }
}

// Utility functions

std::string vectorToString(std::vector<Population> vec) {
  std::string str = "[";
  for (size_t i = 0; i < vec.size(); i++) {
    if(i == vec.size() - 1) {
      str += std::to_string(vec[i].population) + "]"; // last element
    } else {
      str += std::to_string(vec[i].population) + ", "; // other elements
    }
  }
  return str;
}

void quickSwap(std::vector<Population> &vec, int i1, int i2){
  if(i1 == i2) {return;}
  Population temp = vec[i1];
  vec[i1] = vec[i2];
  vec[i2] = temp;
}

bool validateArguments(int argc, char **argv) {
  if (argc < 5 || argc > 6) {
    std::cout << "Usage: ./QuickSort [DatasetFileName].csv [PivotStrategy] [Threshold] [OutputFileName].csv [Verbose]"  // any usage error, print usage
              << std::endl; 
    return false;
  }
  if(argv[2][0] != 'l' && argv[2][0] != 'r' && argv[2][0] != 'm') {
    std::cout << "PivotStrategy must be 'l'(last), 'r'(random) or 'm'(median) !" << std::endl; 
    return false;
  }

  try{
    std::stoi(argv[3]); // try to convert threshold to integer
  }
  catch(std::invalid_argument &error) { // if not an integer, print error
    std::cout << "Threshold must be an integer !" << std::endl; 
    return false;
  }

  const std::regex pattern("^[a-zA-Z0-9]+\\.csv$"); // regex pattern for csv files
  if (!std::regex_match(argv[1], pattern) || !std::regex_match(argv[4], pattern)) { // if the input file and output file are not a csv file, print error
    std::cout << "DatasetFileName and OutputFileName must end with '.csv' !" << std::endl;
    return false;
  }

  if(argc == 6 && argv[5][0] != 'v') {
    std::cout << "Verbose must be given as 'v' !" << std::endl; 
    return false;
  }
  return true;
}

// IO functions

void readFromCsv(const std::string fileName, std::vector<Population> &vec) {
  std::ifstream file("./Data/" + fileName); // data folder is in the same directory as the executable
  if(!file.is_open()) {
    std::cout << "File could not be opened !" << std::endl; // check whether the file is opened
    return;
  }
  std::string line;
  int entity;
  while(std::getline(file, line)) {
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> row;
    while(std::getline(ss, item, ';')) {
      row.push_back(item); // split the line by ';' and push to vector to get the second element
    }
    entity = std::stoi(row[1]); // convert population(second item) to integer
    vec.push_back(Population{line, entity}); // create Population and push to vector
  }
}

void writeToCsv(const std::string fileName, const std::vector<Population> &vec) {
  std::ofstream file("./Data/" + fileName, std::ios::out | std::ios::trunc); // open file in trunc mode to overwrite, create if not exists
  if(!file.is_open()) {
    std::cout << "File could not be opened ! writee" << std::endl; // check whether the file is opened
    return;
  }
  for(size_t i = 0; i < vec.size(); i++) {
    file << vec[i].city << "\n";  // write (city;population) to file
  }
}

void writeLogger(const std::string fileName, const std::vector<Logger> &vec) {
  std::ofstream file(fileName, std::ios::out | std::ios::trunc); // open file in trunc mode to overwrite, create if not exists
  if(!file.is_open()) {
    std::cout << "File could not be opened !" << std::endl; // check whether the file is opened
    return;
  }
  for(size_t i = 0; i < vec.size(); i++) {
    std::string line = "Pivot: " + std::to_string(vec[i].pivot) + " Array: " + vec[i].array + "\n"; // write logger to file in desired format
    file << line;
  }
}

