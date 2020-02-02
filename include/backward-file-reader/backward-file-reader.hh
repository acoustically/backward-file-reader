#ifndef __SILLA_BACKWARD_FILE_READER_BACKWARD_FILE_READER_HH__
#define __SILLA_BACKWARD_FILE_READER_BACKWARD_FILE_READER_HH__


#include <fstream>
#include <string>


namespace silla {

class BackwardFileReader {
  public:
    BackwardFileReader(const std::string& filename);
    ~BackwardFileReader();

    long GetSize();
    std::string GetLine();
    bool IsEof();

  private:
    std::ifstream fin_;
    long file_length_;
    long data_length_;
    char* buffer_;
    long buffer_length_;
    long cursor_;

    int FitBufferLength(const int& length);
    void ExpandBuffer();
    void InitBuffer();
    void FillBuffer();
    long GetLineLength();
    

    static const long DEFAULT_BUFFER_LENGTH_;
};

}


#endif

