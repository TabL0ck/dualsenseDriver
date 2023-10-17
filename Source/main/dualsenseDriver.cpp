#include "dualsense.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  dualsense ds;
  const char *dev_serial = NULL;
  if (!dualsense_init(&ds, dev_serial)) {
    return -1;
  }
  batteryCharge(&ds);
  std::cout << (uint32_t)ds.battery.type << "\t"
            << (uint32_t)ds.battery.currentCharge << std::endl;
  return 0;
}
