#include <iostream>
#include <backward-file-reader/backward-file-reader.hh>
#include <chrono>


int main(int argv, char** argc) {
  silla::BackwardFileReader reader(argc[1]);
  std::cout << reader.GetSize() << std::endl;
  while(!reader.IsEof()) {
    std::cout << "line << " << reader.GetLine() << std::endl;
  }

  return 0;
}
