#include "dualsense.hpp"

bool dualsense_init(dualsense *ds, const char *serial) {
  bool retVal = false;
  bool isFound = false;
  struct hid_device_info *devs = hid_enumerate(DS_VID, DS_PID);
  struct hid_device_info *dev = devs;

  memset(ds, 0, sizeof(*ds));
  ds->connection = CONTROLLER_DISCONNECTED;

  while (devs) {
    if (compare_serial(serial, dev->serial_number)) {
      isFound = true;
      break;
    }

    dev = dev->next;
  }

  if (!isFound) {
    if (serial)
      fprintf(stderr, "Device '%s' not found\n", serial);
    else
      fprintf(stderr, "No device found\n");

    retVal = false;
    goto ret;
  } else {
    wchar_t *serial_number = dev->serial_number;
    ds->dev = hid_open(DS_VID, DS_PID, dev->serial_number);
    if (!ds->dev) {
      fprintf(stderr, "Failde to open device: %ls\n", hid_error(NULL));
      retVal = false;
      goto ret;
    }

    if (wcslen(serial_number) != 17) {
      fprintf(stderr, "Invalid device serial number: %ls\n", serial_number);

      retVal = false;
      goto ret;
    }

    for (uint16_t i = 0; i < 18; ++i) {
      char c = serial_number[i];

      ds->MAC_address[i] = c;

      switch (dev->interface_number) {
      case 3:
        ds->connection = CONTROLLER_WIRE;
        break;
      case -1:
        ds->connection = CONTROLLER_BT;
        break;
      }
      retVal = true;
    }
  }

ret:
  if (devs)
    hid_free_enumeration(devs);
  return retVal;
}

bool check_connection(dualsense *ds) {
  struct hid_device_info *devs = hid_enumerate(DS_VID, DS_PID);
  if (devs == nullptr)
    return false;

  return compare_serial(ds->MAC_address, devs->serial_number);
}
