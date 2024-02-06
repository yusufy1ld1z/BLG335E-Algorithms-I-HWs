/**
  BLG335E - Analysis of Algorithms I - Project 2
  Author: Yusuf Yıldız
  Student ID: 150210006
  Date: 14.12.2023 
*/

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <climits>
#include <cmath>
#include <chrono>

/**
 * @file Heapsort.cpp
 * @brief This file contains the implementation of the max heap building and sorting algorithms.
 */

/**
 * @brief Represents a population data structure for sorting.
 */
struct Population {
  Population(std::string city, int population) : city(city), population(population) {}
  std::string city; ///< City name (city;population) is taken as whole for simplicity
  int population;   ///< Population count
};

// int COMPARISON_COUNT = 0; // Global variable for comparison count

// Utility Functions

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
bool validate_arguments(int argc, char **argv);

/**
 * @brief Removes the BOM(Byte Order Mark) from the input file.
 * @param file File to be read.
 */
void removeBOM(std::ifstream& file);

// IO Functions

/**
 * @brief Writes the vector to a csv file.

 * This function can be used for writing the output of the algorithm or the vector itself depending on the function in which it is called.

 * @param fileName Name of the file to be written.
 * @param vec Vector to be written to the file.
 * @param mode Mode of the write operation. 'o' for output, 'v' for vector.
 * @param out Output string to be written to the file.
 */
void write_to_csv(const std::string fileName, const std::vector<Population> &vec, char mode, const std::string out);

/**
 * @brief Reads the csv file and creates a vector of Population.
 * @param fileName Name of the file to be read.
 * @param vec Vector to be filled with Population.
 */
void read_from_csv(const std::string fileName, std::vector<Population> &vec);

// Heap Functions

/**
 * @brief Creates the binary max heap structure for given index recursively.
 * @param vec Vector to be built as a max heap.
 * @param i Index of the element to be max heapified.
 * @param size Size of the vector.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void max_heapify(std::vector<Population> &vec, int i, int size, const std::string fileName, bool writeToFile);

/**
 * @brief Builds a binary max heap from the vector.
 * @param vec Vector to be built as a max heap.
 * @param size Size of the vector.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void build_max_heap(std::vector<Population> &vec, int size, const std::string fileName, bool writeToFile);

/**
 * @brief Sorts the vector using heapsort algorithm.
 * @param vec Vector to be sorted.
 * @param size Size of the vector.
 * @param fileName Name of the file to be written.
 */
void heapsort(std::vector<Population> &vec, int size, const std::string fileName);

/**
 * @brief Inserts a new element to the heap.
 * @param vec Vector to be inserted.
 * @param city City name to be inserted.
 * @param key Population count of the city to be inserted.
 * @param fileName Name of the file to be written.
 */
void max_heap_insert(std::vector<Population> &vec, std::string city, int key, const std::string fileName);

/**
 * @brief Extracts the maximum element from the heap.
 * @param vec Vector to be extracted.
 * @param fileName Name of the file to be written.
 * @return The maximum element of the heap.
 */
Population heap_extract_max(std::vector<Population> &vec, const std::string fileName);

/**
 * @brief Increases the key of the element at given index.
 * @param vec Vector to be increased.
 * @param i Index of the element to be increased.
 * @param key New population count of the city.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void heap_increase_key(std::vector<Population> &vec, int i, int key, const std::string fileName, bool writeToFile);

/**
 * @brief Returns the maximum element of the heap.
 * @param vec Vector to be searched.
 * @param fileName Name of the file to be written.
 * @return The maximum element of the heap.
 */
Population heap_maximum(std::vector<Population> &vec, const std::string fileName);

// d-ary Heap Functions

/**
 * @brief Creates the d-ary max heap structure for given index recursively.

 * This function is not callable from command line, it is used in dary_build_max_heap function, and creates the d-ary max heap structure for given index recursively.

 * @param vec Vector to be built as a max heap.
 * @param i Index of the element to be max heapified.
 * @param size Size of the vector.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void dary_max_heapify(std::vector<Population> &vec, int i, int size, int d, const std::string fileName, bool writeToFile); // not callable from command line

/**
 * @brief Builds a d-ary max heap from the vector.

 * This function is not callable from command line, it is used in building d-ary heaps before specific function calls.

 * @param vec Vector to be built as a max heap.
 * @param size Size of the vector.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void dary_build_max_heap(std::vector<Population> &vec, int size, int d, const std::string fileName, bool writeToFile); // not callable from commmand line

/**
 * @brief Calculates the height of the d-ary heap.
 * @param size Size of the vector.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 * @return The height of the d-ary heap.
 */
int dary_calculate_height(int size, int d, const std::string fileName);

/**
 * @brief Extracts the maximum element from the d-ary heap.
 * @param vec Vector to be extracted.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 * @return The maximum element of the d-ary heap.
 */
Population dary_extract_max(std::vector<Population> &vec, int d, const std::string fileName);

/**
 * @brief Inserts a new element to the d-ary heap.
 * @param vec Vector to be inserted.
 * @param city City name to be inserted.
 * @param key Population count of the city to be inserted.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 */
void dary_insert_element(std::vector<Population> &vec, std::string city, int key, int d, const std::string fileName);

/**
 * @brief Increases the key of the element at given index.
 * @param vec Vector to be increased.
 * @param i Index of the element to be increased.
 * @param key New population count of the city.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 * @param writeToFile Whether to write the output to file or not.
 */
void dary_increase_key(std::vector<Population> &vec, int i, int key, int d, const std::string fileName, bool writeToFile);

/**
 * @brief Sorts the vector using heapsort algorithm.

 * This function is not callable from command line, it is used for sorting d-ary heaps for testing purposes.

 * @param vec Vector to be sorted.
 * @param size Size of the vector.
 * @param d Number of children of each node.
 * @param fileName Name of the file to be written.
 */
void dary_heapsort(std::vector<Population> &vec, int size, int d, const std::string fileName);

/**
 * @brief The main function that orchestrates the max heap process based on command line arguments.
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return 0 if successful, 1 otherwise.
 */
int main(int argc, char **argv){

  std::string input_file_name; // mandatory parameters
  std::string output_file_name;
  std::string function;

  std::string paramI; // additional parameters
  std::string paramD;
  std::string paramK;

  int i = 0;
  int d = 0;
  int k = 0;

  bool isIGiven = false; // flags for additional parameters
  bool isDGiven = false;
  bool isKGiven = false;

  if(!validate_arguments(argc, argv)) { // validate arguments
    return 1;
  }else{
    input_file_name = argv[1];
    function = argv[2];
    output_file_name = argv[3];
    if(argc > 4) {
      for(int i = 4; i < argc; i++) { // control the additional parameters
        switch(argv[i][0]) {
          case 'i':{          
            paramI = argv[i];
            isIGiven = true; 
            break;
          }
          case 'd':{
            paramD = argv[i];
            isDGiven = true; 
            break;
          }
          case 'k':{
            paramK = argv[i];
            isKGiven = true; 
            break;
          }
        }
      }
    }
  }

  std::vector<Population> population_data; // created for population data

  read_from_csv(input_file_name, population_data); // read from csv

  // *** TEST ***

  // dary_build_max_heap(population_data, population_data.size(), 3, output_file_name, true); // test for dary_build_max_heap

  // return 0;

  // build_max_heap(population_data, population_data.size(), output_file_name, true); // test for build_max_heap

  // return 0;

  // dary_heapsort(population_data, population_data.size(), 5, output_file_name); // test for dary_heapsort
  
  // return 0;

  // *** TEST ***

  auto is_numeric = [](const std::string &str) -> bool { // check whether the string is numeric or not, this function also controls the negative numbers
    return !str.empty() && std::find_if(str.begin(), 
      str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end(); // control the string digit by digit to be numeric
  };

  if (function == "max_heapify") { // max_heapify function
    if(!isIGiven) { // first control the additional parameter i
      std::cerr << "Additional parameter 'i' must be given for max_heapify!" << std::endl;
      return 1;
    }
    if(!is_numeric(paramI.substr(1))) { // control the additional parameter i to be numeric
      std::cerr << "Additional parameter 'i' must be followed by a number but '" << paramI << "' is given!" << std::endl;
      return 1;
    } else {
      i = std::stoi(paramI.substr(1));
      if (i > static_cast<int>(population_data.size()) || i == 0) { // i must be smaller than the size of the heap 
        std::cerr << "Index 'i' is out of range, the size of the input is '" << population_data.size() << "' but '" << i << "' is given!" << std::endl;
        return 1;
      }
      max_heapify(population_data, i - 1, population_data.size(), output_file_name, true); // for index, i - 1 is given
    }
  } 

  else if (function == "build_max_heap") { // build_max_heap function
    build_max_heap(population_data, population_data.size(), output_file_name, true);
  } 

  else if (function == "heapsort") { // heapsort function
    auto start = std::chrono::high_resolution_clock::now();
    heapsort(population_data, population_data.size(), output_file_name); // it already builds the heap inside of itself
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // in nanoseconds
    std::cout << "Time taken by Heapsort : " << duration.count() << " ns." << std::endl;
  } 

  else if (function == "max_heap_insert") { // max_heap_insert function
    if (!isKGiven) { // first control the additional parameter k
      std::cerr << "Additional parameter 'k' must be given for max_heap_insert!" << std::endl;
      return 1;
    }
    std::string arg = paramK;
    size_t underscore1 = arg.find('_', 0); // first underscore
    size_t underscore2 = arg.find('_', underscore1 + 1); // second underscore

    if (underscore1 != std::string::npos && underscore2 != std::string::npos) { // control the additional parameter k to be in a format of k_city_population
      std::string city = arg.substr(underscore1 + 1, underscore2 - underscore1 - 1);
      if(!is_numeric(arg.substr(underscore2 + 1))){ // control the additional parameter k to be numeric
        std::cerr << "Additional parameter 'k' must end with a number but '" << paramK << "' is given!" << std::endl;
        return 1;
      } else {
        k = std::stoi(arg.substr(underscore2 + 1));
        build_max_heap(population_data, population_data.size(), output_file_name, false); // first build the max heap
        max_heap_insert(population_data, city, k, output_file_name);  // k_city_population
      }
    } else { // invalid format
      std::cerr << "Additional parameter 'k' must be in a format of 'k_city_population' but '" << paramK << "' is given!" << std::endl;
    }
  } 
  
  else if (function == "heap_extract_max") { // heap_extract_max function
    build_max_heap(population_data, population_data.size(), output_file_name, false); // first build the max heap
    heap_extract_max(population_data, output_file_name); // output does not matter for the rest of the code so writeToFile is discarded
  } 
  
  else if (function == "heap_increase_key") { // heap_increase_key function
    if(!isIGiven) { // first control the additional parameter i
      std::cerr << "Additional parameter 'i' must be given for heap_increase_key!" << std::endl;
      return 1;
    } else if (!isKGiven) { // secondly control the additional parameter k
      std::cerr << "Additional parameter 'k' must be given for heap_increase_key!" << std::endl;
      return 1;
    } 

    if(!is_numeric(paramI.substr(1))) { // control the additional parameter i to be numeric
      std::cerr << "Additional parameter 'i' must be followed by a number but '" << paramI << "' is given!" << std::endl;
      return 1;
    } else if (!is_numeric(paramK.substr(1))) { // control the additional parameter k to be numeric
      std::cerr << "Additional parameter 'k' must be followed by a number but '" << paramK << "' is given!" << std::endl;
      return 1;
    } else {
      i = std::stoi(paramI.substr(1));
      k = std::stoi(paramK.substr(1));
      if (i > static_cast<int>(population_data.size()) || i == 0) { // i must be smaller than the size of the heap
        std::cerr << "Index 'i' is out of range, the size of the input is '" << population_data.size() << "' but '" << i << "' is given!" << std::endl;
        return 1;
      }
      build_max_heap(population_data, population_data.size(), output_file_name, false); // first build the max heap
      heap_increase_key(population_data, i - 1, k, output_file_name, true); // for index, i - 1 is given
    }
  } 
   
  else if (function == "heap_maximum") { // heap_maximum function
    build_max_heap(population_data, population_data.size(), output_file_name, false); // first build the max heap
    heap_maximum(population_data, output_file_name); // output does not matter for the rest of the code so it is discarded
  } 
  
  else if (function == "dary_calculate_height") { // dary_calculate_height function
    if(!isDGiven) { // first control the additional parameter d
      std::cerr << "Additional parameter 'd' must be given for dary_calculate_height!" << std::endl;
      return 1;
    }

    if(!is_numeric(paramD.substr(1))) { // control the additional parameter d to be numeric
      std::cerr << "Additional parameter 'd' must be followed by a number but '" << paramD << "' is given!" << std::endl;
      return 1;
    } else {
      d = std::stoi(paramD.substr(1));
      if (d < 2 || d > static_cast<int>(population_data.size())) { // d must be greater than 1 to be a valid heap, and also it must be smaller than the size of the heap to get built as a valid heap
        std::cerr << "Additional parameter 'd' must be greater than 1 and smaller than the size of the input, which is " << population_data.size() << ", but '" << d << "' is given!" << std::endl;
        return 1;
      }
      dary_calculate_height(population_data.size(), d, output_file_name); // no need to build the heap
    }
  } 
  
  else if (function == "dary_extract_max") { // dary_extract_max function
    if(!isDGiven) { // first control the additional parameter d
      std::cerr << "Additional parameter 'd' must be given for dary_extract_max!" << std::endl;
      return 1;
    }

    if(!is_numeric(paramD.substr(1))) { // control the additional parameter d to be numeric
      std::cerr << "Additional parameter 'd' must be followed by a number but '" << paramD << "' is given!" << std::endl;
      return 1;
    } else {
      d = std::stoi(paramD.substr(1));
      if (d < 2 || d > static_cast<int>(population_data.size())) { // d must be greater than 1 to be a valid heap, and also it must be smaller than the size of the heap to get built as a valid heap
        std::cerr << "Additional parameter 'd' must be greater than 1 and smaller than the size of the input, which is " << population_data.size() << ", but '" << d << "' is given!" << std::endl;
        return 1;
      }
      dary_build_max_heap(population_data, population_data.size(), d, output_file_name, false); // first build the max heap
      dary_extract_max(population_data, d, output_file_name); // output does not matter for the rest of the code so it is discarded
    }
  } 
  
  else if (function == "dary_insert_element") { // dary_insert_element function
    if(!isDGiven) { // first control the additional parameter d
      std::cerr << "Additional parameter 'd' must be given for dary_insert_element!" << std::endl;
      return 1;
    } else if (!isKGiven) { // secondly control the additional parameter k
      std::cerr << "Additional parameter 'k' must be given for dary_insert_element!" << std::endl;
      return 1;
    }

    std::string arg = paramK;
    size_t underscore1 = arg.find('_', 0); // first underscore
    size_t underscore2 = arg.find('_', underscore1 + 1); // second underscore

    if (underscore1 != std::string::npos && underscore2 != std::string::npos) { // control the additional parameter k to be in a format of k_city_population
      std::string city = arg.substr(underscore1 + 1, underscore2 - underscore1 - 1);
      if(!is_numeric(arg.substr(underscore2 + 1))){ // control the additional parameter k to be numeric
        std::cerr << "Additional parameter 'k' must end with a number but '" << paramK << "' is given!" << std::endl;
        return 1;
      } else if (!is_numeric(paramD.substr(1))) { // control the additional parameter d to be numeric
        std::cerr << "Additional parameter 'd' must be followed by a number but '" << paramD << "' is given!" << std::endl;
        return 1;
      } else {
        d = std::stoi(paramD.substr(1));
        k = std::stoi(arg.substr(underscore2 + 1));
      if (d < 2 || d > static_cast<int>(population_data.size())) { // d must be greater than 1 to be a valid heap, and also it must be smaller than the size of the heap to get built as a valid heap
        std::cerr << "Additional parameter 'd' must be greater than 1 and smaller than the size of the input, which is " << population_data.size() << ", but '" << d << "' is given!" << std::endl;
        return 1;
      }
        dary_build_max_heap(population_data, population_data.size(), d, output_file_name, false); // first build the max heap
        dary_insert_element(population_data, city, k, d, output_file_name);  // k_city_population
      }
    } else { // invalid format
      std::cerr << "Additional parameter 'k' must be in a format of 'k_city_population' but '" << paramK << "' is given!" << std::endl;
    }
  } 
  
  else if (function == "dary_increase_key") { // dary_increase_key function
    if(!isIGiven) { // first control the additional parameter i
      std::cerr << "Additional parameter 'i' must be given for dary_increase_key!" << std::endl;
      return 1;
    } else if (!isDGiven) { // secondly control the additional parameter d
      std::cerr << "Additional parameter 'd' must be given for dary_increase_key!" << std::endl;
      return 1;
    } else if (!isKGiven) { // lastly control the additional parameter k
      std::cerr << "Additional parameter 'k' must be given for dary_increase_key!" << std::endl;
      return 1;
    }

    if(!is_numeric(paramI.substr(1))) { // control the additional parameter i to be numeric
      std::cerr << "Additional parameter 'i' must be followed by a number but '" << paramI << "' is given!" << std::endl;
      return 1;
    } else if (!is_numeric(paramK.substr(1))) { // control the additional parameter k to be numeric
      std::cerr << "Additional parameter 'k' must be followed by a number but '" << paramK << "' is given!" << std::endl;
      return 1;
    } else if (!is_numeric(paramD.substr(1))) { // control the additional parameter d to be numeric
      std::cerr << "Additional parameter 'd' must be followed by a number but '" << paramD << "' is given!" << std::endl;
      return 1;
    } else {
      i = std::stoi(paramI.substr(1));
      d = std::stoi(paramD.substr(1));
      k = std::stoi(paramK.substr(1));
      if (i > static_cast<int>(population_data.size()) || i == 0) { // i must be smaller than the size of the heap
        std::cerr << "Index 'i' is out of range, the size of the input is '" << population_data.size() << "' but '" << i << "' is given!" << std::endl;
        return 1;
      }
      if (d < 2 || d > static_cast<int>(population_data.size())) { // d must be greater than 1 to be a valid heap, and also it must be smaller than the size of the heap to get built as a valid heap
        std::cerr << "Additional parameter 'd' must be greater than 1 and smaller than the size of the input, which is " << population_data.size() << ", but '" << d << "' is given!" << std::endl;
        return 1;
      }
      dary_build_max_heap(population_data, population_data.size(), d, output_file_name, false); // first build the max heap
      dary_increase_key(population_data, i - 1, k, d, output_file_name, true); // for index, i - 1 is given
    }
  }

  // std::cout << "Total comparison made by heapsort : " << COMPARISON_COUNT << std::endl; // print the total comparison count
  return 0;
}

// Utility Functions

void quickSwap(std::vector<Population> &vec, int i1, int i2){ // swap two elements in a vector
  if(i1 == i2) {return;}
  Population temp = vec[i1];
  vec[i1] = vec[i2];
  vec[i2] = temp;
}

bool validate_arguments(int argc, char **argv) { // validate arguments
  if (argc < 4 || argc > 7) {
    std::cerr << "Usage: ./Heapsort [DatasetFileName].csv [FunctionName] [OutputFileName].csv [AdditionalParameters - i, d, k]"  // any usage error, print usage
              << std::endl; 
    return false;
  }

  std::vector<std::string> validFunctions{"max_heapify", "build_max_heap", "heapsort", "max_heap_insert", "heap_extract_max", "heap_increase_key",
        "heap_maximum", "dary_calculate_height", "dary_extract_max", "dary_insert_element", "dary_increase_key"}; // valid functions

  auto it = std::find(validFunctions.begin(), validFunctions.end(), argv[2]); // find the function in the vector
  if (it == validFunctions.end()) { // if not found, print error
    std::cerr << "FunctionName must be one of the following: 'max_heapify, build_max_heap, heapsort, max_heap_insert, " <<
        "heap_extract_max, heap_increase_key, heap_maximum, dary_calculate_height, dary_extract_max, dary_insert_element, dary_increase_key' but '" << argv[2] << "' is given!" << std::endl;
    return false;
  }

  auto is_valid_additional_parameter = [](char param) -> bool { // check whether the additional parameter is valid or not
    return (param == 'i' || param == 'd' || param == 'k');
  };

  if(argc > 4) {
    for(int i = 4; i < argc; i++) {
      if(!is_valid_additional_parameter(argv[i][0])) { // if the additional parameter is not valid, print error
        std::cerr << "AdditionalParameters must be one of the following: i, d, k but '" << argv[i][0] << "' is given!" << std::endl;
        return false;
      }
    }
  }

  const std::regex pattern("^[a-zA-Z0-9]+\\.csv$"); // regex pattern for csv files
  if (!std::regex_match(argv[1], pattern) || !std::regex_match(argv[3], pattern)) { // if the input file and output file are not a csv file, print error
    std::cerr << "DatasetFileName and OutputFileName must end with '.csv'!" << std::endl;
    return false;
  }

  return true; // if everything is ok, return true
}

void removeBOM(std::ifstream& file) { // remove BOM from the file
  char buffer[3];
  file.read(buffer, sizeof(buffer)); // read the first 3 bytes

  if (file.gcount() == 3 &&
    static_cast<unsigned char>(buffer[0]) == 0xEF &&
    static_cast<unsigned char>(buffer[1]) == 0xBB &&
    static_cast<unsigned char>(buffer[2]) == 0xBF) {
    // BOM detected, skip these bytes
    file.seekg(3);
  } else {
    // No BOM, rewind to the beginning
    file.seekg(0);
  }
}

// IO Functions

void write_to_csv(const std::string fileName, const std::vector<Population> &vec, char mode, const std::string out = "") {
  std::ofstream file("./Data/" + fileName, std::ios::out | std::ios::trunc); // open file in trunc mode to overwrite, create if not exists
  if(!file.is_open()) {
    std::cerr << "File could not be opened at the path '" << "./Data" + fileName << "'!" << std::endl; // check whether the file is opened
    return;
  }
  if(mode == 'o') { // for output option, write the output string to file
    file << out << "\n";
  }
  else if(mode == 'v') { // for vector option write the whole vector to file
    for(size_t i = 0; i < vec.size(); i++) {
      file << vec[i].city << "\n";  // write (city;population) to file
    }
  }else {
    std::cerr << "Invalid mode !(The mode must be 'o' or 'v') but '" << std::string(1, mode) << "' is given!" << std::endl;
  }
}

void read_from_csv(const std::string fileName, std::vector<Population> &vec) {
  std::ifstream file("./Data/" + fileName, std::ios::binary); // data folder is in the same directory as the executable
  if(!file.is_open()) {
    std::cerr << "File could not be opened at the path '" << "./Data" + fileName << "'!" << std::endl; // check whether the file is opened
    return;
  }

  removeBOM(file); // Remove BOM if present

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

// Heap Functions

void max_heapify(std::vector<Population> &vec, int i, int size, const std::string fileName, bool writeToFile) {
  int left = 2 * i + 1; // left child
  int right = 2 * i + 2; // right child
  int largest = i;
  if(left < size && vec[left].population > vec[largest].population) { // if left child is greater than the parent, largest is left child
    largest = left;
  }
  // COMPARISON_COUNT+=2; // 2 comparison is made in the if statement above
  if(right < size && vec[right].population > vec[largest].population) { // if right child is greater than the parent, largest is right child
    largest = right;
  }
  // COMPARISON_COUNT+=2; // 2 comparison is made in the if statement above
  if(largest != i) { // if largest is not the parent, swap the parent with the largest child and call max_heapify recursively
    quickSwap(vec, i, largest);
    max_heapify(vec, largest, size, fileName, writeToFile); // call max_heapify recursively
  }
  // COMPARISON_COUNT+=1; // 1 comparison is made in the if statement above
  if(writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v');
}

void build_max_heap(std::vector<Population> &vec, int size, const std::string fileName, bool writeToFile) {
  for(int i = (size - 1) / 2; i >= 0; i--) { // start from the last parent and call max_heapify recursively
    max_heapify(vec, i, size, fileName, false);
  }
  // COMPARISON_COUNT+=((size - 1) / 2 + 2); // total comparison made in for loop above
  if(writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v');
}

void heapsort(std::vector<Population> &vec, int size, const std::string fileName) {
  build_max_heap(vec, size, fileName, false);                               // first build the max heap
  for(int i = size - 1; i >= 1; i--) {                                      // start from the last element and swap it with the first element, then call max_heapify recursively
     // max_heapify is called with i as the size of the heap, 
    quickSwap(vec, 0, i);                                                   // which is decreased by 1 at each iteration, so the last element is ignored at each iteration,   
    max_heapify(vec, 0, i, fileName, false);                                // and as a result, the output array becomes in ascending order
  }
  // COMPARISON_COUNT+=((size - 1) + 1); // total comparison made in for loop above
  write_to_csv(fileName, vec, 'v'); // write the vector to file
}

void max_heap_insert(std::vector<Population> &vec, std::string city, int key, const std::string fileName) {
  vec.push_back(Population(city + ";" + std::to_string(key), INT_MIN)); // push the new element with INT_MIN popuation to the end of the vector
  heap_increase_key(vec, vec.size() - 1, key, fileName, false); // increase the key of the last element with the given key
  write_to_csv(fileName, std::vector<Population>(), 'o', city + ";" + std::to_string(key) + "\n"); // passed vector is empty because we do not want to write the whole vector to file
}

Population heap_extract_max(std::vector<Population> &vec, const std::string fileName) {
  if(vec.size() < 1) {
    std::cerr << "Heap underflow, there is no element in the heap!" << std::endl; // if there is no element in the heap, print error
    return Population("", INT_MIN);
  }
  Population max = vec[0]; // get the first element, it is the max element
  write_to_csv(fileName, std::vector<Population>(), 'o', max.city + "\n"); // passed vector is empty because we do not want to write the whole vector to file
  vec[0] = vec[vec.size() - 1]; // swap the first element, which is largest, with the last element of the heap
  vec.pop_back(); // pop the last element
  max_heapify(vec, 0, vec.size(), fileName, false); // call the max_heapify with index 0 to locate the new first element
  return max;
}

void heap_increase_key(std::vector<Population> &vec, int i, int key, const std::string fileName, bool writeToFile) {
  if(key < vec[i].population) { // if the new key is smaller than the current key, print error
    std::cerr << "New key, which is '" << key << "', is smaller than the current key '" << vec[i].population << "' for the city '" << vec[i].city.substr(0, vec[i].city.find(';')) << "'!" << std::endl;
    return;
  }
  vec[i].city = vec[i].city.substr(0, vec[i].city.find(';')) + ";" + std::to_string(key); // change the city's population, this line is required because of the structure 
  vec[i].population = key;                                                                // of the Population struct, as we hold the data as whole string, we need to change the population
                                                                                          // of the city in the string
  while(i > 0 && vec[(i-1)/2].population < vec[i].population) { // while the parent is smaller than the child, swap them and go up
    quickSwap(vec, i, (i-1)/2);
    i = (i-1)/2;
  }

  if (writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v');
}

Population heap_maximum(std::vector<Population> &vec, const std::string fileName) {
  write_to_csv(fileName, std::vector<Population>(), 'o', vec[0].city + "\n"); // passed vector is empty because we do not want to write the whole vector to file
  return vec[0]; // return the first element, it is the max element
}

// d-ary Heap Functions

void dary_max_heapify(std::vector<Population> &vec, int i, int size, int d, const std::string fileName, bool writeToFile) {
  std::vector<int> indices;
  for(int j = 1; j <= d; j++) {
    int idx = (d * i) + j;
    idx < size ? indices.push_back(idx) : indices.push_back(-1); // if the index is out of range, push -1 to the vector
  }
  int largest = i;
  for(int j = 0; j < d; j++) {
    if(indices[j] != -1 && vec[indices[j]].population > vec[largest].population) { // if the child is not -1 and greater than the parent, largest is the current child
      largest = indices[j];
    }
  }

  if(largest != i) { // if largest is not the parent, swap the parent with the largest child and call dary_max_heapify recursively
  quickSwap(vec, i, largest);
  dary_max_heapify(vec, largest, size, d, fileName, writeToFile); // call dary_max_heapify recursively
  }
  if(writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v');
}

void dary_build_max_heap(std::vector<Population> &vec, int size, int d, const std::string fileName, bool writeToFile) {
  for(int i = (size - 1) / d; i >= 0; i--) { // start from the last parent and call dary_max_heapify recursively
    dary_max_heapify(vec, i, size, d, fileName, false);
  }
  if(writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v');
}

int dary_calculate_height(int size, int d, const std::string fileName) {
  int height = static_cast<int>(std::ceil(std::log(size * d - size + 1) / std::log(d))) - 1; // this is the formula for calculating the height of a d-ary heap
  write_to_csv(fileName, std::vector<Population>(), 'o', "Height : " + std::to_string(height) + "\n"); // passed vector is empty because we do not want to write the whole vector to file
  return height;
}

Population dary_extract_max(std::vector<Population> &vec, int d, const std::string fileName) {
  if(vec.size() < 1) {
    std::cerr << "Heap underflow, there is no element in the heap!" << std::endl; // if there is no element in the heap, print error
    return Population("", INT_MIN);
  }
  Population max = vec[0]; // get the first element, it is the max element
  write_to_csv(fileName, std::vector<Population>(), 'o', max.city + "\n"); // passed vector is empty because we do not want to write the whole vector to file
  vec[0] = vec[vec.size() - 1]; // swap the first element, which is the largest, with the last element of the heap
  vec.pop_back(); // pop the last element
  dary_max_heapify(vec, 0, vec.size(), d, fileName, false); // call the dary_max_heapify with index 0 to locate the new first element
  return max;
}

void dary_insert_element(std::vector<Population> &vec, std::string city, int key, int d, const std::string fileName) {
  vec.push_back(Population(city + ";" + std::to_string(key), INT_MIN)); // push the new element with INT_MIN popuation to the end of the vector
  dary_increase_key(vec, vec.size() - 1, key, d, fileName, false); // increase the key of the last element with the given key
  write_to_csv(fileName, std::vector<Population>(), 'o', city + ";" + std::to_string(key) + "\n"); // passed vector is empty because we do not want to write the whole vector to file
}

void dary_increase_key(std::vector<Population> &vec, int i, int key, int d, const std::string fileName, bool writeToFile) {
  if(key < vec[i].population) { // if the new key is smaller than the current key, print error
    std::cerr << "New key, which is '" << key << "', is smaller than the current key '" << vec[i].population << "' for the city '" << vec[i].city.substr(0, vec[i].city.find(';')) << "'!" << std::endl;
    return;
  }
  vec[i].city = vec[i].city.substr(0, vec[i].city.find(';')) + ";" + std::to_string(key); // change the city's population, this line is required because of the structure 
  vec[i].population = key;                                                                // of the Population struct, as we hold the data as whole string, we need to change the population
                                                                                          // of the city in the string
  while(i > 0 && vec[(i-1)/d].population < vec[i].population) { // while the parent is smaller than the child, swap them and go up
    quickSwap(vec, i, (i-1)/d);
    i = (i-1)/d;
  }

  if (writeToFile) // if writeToFile is true, write the vector to file
    write_to_csv(fileName, vec, 'v'); 
}

void dary_heapsort(std::vector<Population> &vec, int size, int d, const std::string fileName) {
  dary_build_max_heap(vec, size, d, fileName, false); // first build the max heap
  for(int i = size - 1; i >= 1; i--) {                // start from the last element and swap it with the first element, then call dary_max_heapify recursively
    quickSwap(vec, 0, i);                             // max_heapify is called with i as the size of the heap, which is decreased by 1 at each iteration, so the last element is ignored at each iteration
    dary_max_heapify(vec, 0, i, d, fileName, false);  // and as a result, the output array becomes in ascending order
  }
  write_to_csv(fileName, vec, 'v');
}
