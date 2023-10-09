#include "dualsense.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  const char *dev_serial = NULL;
  dualsense ds;
  if (!dualsense_init(&ds, dev_serial)) {
    return -1;
  }
  return 0;
}
