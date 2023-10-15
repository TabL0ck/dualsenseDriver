#include "dualsense.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  dualsense ds;
  const char *dev_serial = NULL;
  if (!dualsense_init(&ds, dev_serial)) {
    return -1;
  }
  while (true) {
    std::cout << check_connection(&ds) << std::endl;
    sleep(1);
  }
  return 0;
}
