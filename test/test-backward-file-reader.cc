#include <iostream>
#include <backward-file-reader/backward-file-reader.hh>
#include <chrono>


int main(int argv, char** argc) {
  silla::BackwardFileReader reader(argc[1]);
  std::cout << reader.GetSize() << std::endl;

 
  auto start = std::chrono::high_resolution_clock::now();
  while(!reader.IsEof()) {
    std::cout << "line << " << reader.GetLine() << std::endl;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  double duration_ = duration.count(); 
  std::cout << "duration = " << duration_ << std::endl;
  return 0;
}
