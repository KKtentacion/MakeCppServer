#include <cstdlib>
#include <iostream>
#include <ostream>

#include <stdio.h>
#include <unistd.h>
int main() {
  FILE *in_file, *out_file;
  int count = 1;
  char buf[20];
  std::cout << "Start reading" << std::endl;
  in_file = fopen("/home/kktenta/cpp_novice/build/Debug/myfifo", "r");
  if (in_file == NULL) {
    std::cout << "Error in open file" << std::endl;
    exit(1);
  }
  while ((count = fread(buf, 1, 20, in_file)) > 0) {
    buf[count] = '\0';
    std::cout << "received from pipe" << buf;
  }
  std::cout << "Start writing" << std::endl;
  fclose(in_file);
  out_file = fopen("myfifo", "w");
  if (out_file == NULL) {
    std::cout << "Error in open file" << std::endl;
    exit(1);
  }
  std::cout << buf << "this is test data for the named pipe example." << std::endl;
  fwrite(buf, 1, 5, out_file);
  fclose(out_file);
  return 0;
}