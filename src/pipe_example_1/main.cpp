#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

int pipe(int fileds[2]);
#define INPUT  0
#define OUTPUT 1

int main() {
  int file_descriptors[2];
  pid_t pid;
  char buf[100];  // 使用字符数组作为缓冲区
  int returned_count;

  pipe(file_descriptors);

  pid = fork();  // 这里要赋值给pid
  if (pid == -1) {
    std::cout << "Error in fork\n";
    exit(1);
  }

  if (pid == 0) {
    std::cout << "in the spawned(child)process...\n";
    close(file_descriptors[INPUT]);
    write(file_descriptors[OUTPUT], "test data", strlen("test data") + 1);  // 写入数据时包括终止符
    exit(0);
  } else {
    std::cout << "in the spawning(parent)process...\n";
    close(file_descriptors[OUTPUT]);
    returned_count      = read(file_descriptors[INPUT], buf, sizeof(buf));
    std::cout << returned_count << " bytes of data received from spawned process: " << buf << std::endl;
  }

  return 0;
}
