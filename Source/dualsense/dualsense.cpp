#include "dualsense.hpp"

bool dualsense_init(dualsense *ds, const char *serial) {
  bool retVal = false;
  bool isFound = false;
  struct hid_device_info *devs = hid_enumerate(DS_VID, DS_PID);
  memset(ds, 0, sizeof(*ds));

  while (devs) {
    std::cout << devs->serial_number << std::endl;
  }

  return retVal;
}
