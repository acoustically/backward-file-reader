#include <backward-file-reader/backward-file-reader.hh>
#include <cstring>
#include <cstdio>

//TEST
#include <iostream>


using namespace silla;

const long BackwardFileReader::DEFAULT_BUFFER_LENGTH_(8192);

BackwardFileReader::BackwardFileReader(const std::string& filename) 
    : fin_(filename, std::ios::in | std::ios::binary | std::ios::ate)
    , file_length_(fin_.tellg())
    , data_length_(0)
    , buffer_length_(0)
    , cursor_(0)
{}

BackwardFileReader::~BackwardFileReader() {
  delete[] buffer_;
}

long BackwardFileReader::GetSize() {
  return file_length_;
}

std::string BackwardFileReader::GetLine() {
  long line_length = GetLineLength();
  long i = data_length_ - cursor_ + 1;
  return std::string(buffer_ + i, buffer_ + i + line_length);
}

bool BackwardFileReader::IsEof() {
  if(cursor_ + 1 >= file_length_) {
    return true;
  }
  return false;
}

long BackwardFileReader::FitBufferLength(const long& buffer_length) {
  if(buffer_length > file_length_) {
    return file_length_;
  } else {
    return buffer_length;
  }
}

void BackwardFileReader::ExpandBuffer() {
  long new_buffer_length = FitBufferLength(buffer_length_ * 2);
  char* new_buffer = new char[new_buffer_length + 1];
  memset(new_buffer, '\0', new_buffer_length + 1);
  std::copy(
        buffer_
      , buffer_ + buffer_length_
      , new_buffer + (new_buffer_length - buffer_length_));
  delete[] buffer_;
  
  buffer_ = new_buffer;
  buffer_length_ = new_buffer_length;
}

void BackwardFileReader::InitBuffer() {
  buffer_length_ = FitBufferLength(DEFAULT_BUFFER_LENGTH_);
  buffer_ = new char[buffer_length_ + 1];
  memset(buffer_, '\0', buffer_length_ + 1);
}

void BackwardFileReader::FillBuffer() {
  long data_end_index = 0;
  long length;
  if(buffer_length_ == 0) {
    InitBuffer();
    length = buffer_length_;
  } else {
    ExpandBuffer();
    data_end_index = buffer_length_ / 2;
    length = buffer_length_ - data_end_index;
  }

  long file_polonger = file_length_ - buffer_length_;
  if(file_polonger < 0) {
    file_polonger = 0;
  }

  fin_.seekg(file_polonger, std::ios::beg);
  fin_.read(buffer_, length);
  data_length_ = strlen(buffer_);
  if(data_length_ > file_length_) {
    data_length_ = file_length_;
  }
}

long BackwardFileReader::GetLineLength() {
  long length = 0;
  while(true) {
    long i = data_length_ - cursor_ - 1;
    if(IsEof()) {
      cursor_ += 2;
      return ++length;
    } 
    if(i < 0) {
      FillBuffer();
      continue;
    }
    cursor_++;
    if( buffer_[i] == '\n') {
      if(i == data_length_ - 1) {
        continue;
      }
      return length;
    } else if(!(length == 0 && buffer_[i] == '\r')) {
      length++;
    }
  }
} 
