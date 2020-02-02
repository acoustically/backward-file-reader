#include <iostream>
#include <fstream>
#include <chrono>


int main(int argv, char** argc) {
  std::ifstream fin(argc[1]);

  auto start = std::chrono::high_resolution_clock::now();
  for (std::string line; getline(fin, line); ) {
    std::cout << "line << " << line << std::endl;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  double duration_ = duration.count(); 
  std::cout << "duration = " << duration_ << std::endl;
}
