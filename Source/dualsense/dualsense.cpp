#include "dualsense.hpp"
#include "utils.hpp"
#include <cstdio>

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

void printGamePadState(const USBGetStateData *obj) {
  std::cout
      << "lStickX: " << (uint32_t)obj->lStick.x << std::endl
      << "lStickY: " << (uint32_t)obj->lStick.y << std::endl
      << "rStickX: " << (uint32_t)obj->rStick.x << std::endl
      << "rStickY: " << (uint32_t)obj->rStick.y << std::endl
      << "lTrigger: " << (uint32_t)obj->trig.left << std::endl
      << "rTrigger: " << (uint32_t)obj->trig.right << std::endl
      << "\n-------------------\n"
      << std::endl
      << "seqNumber: " << (uint32_t)obj->seqNo << std::endl
      << "\n-------------------\n"
      << std::endl
      << "btnSquare: " << (uint32_t)obj->btn.square << std::endl
      << "btnCross: " << (uint32_t)obj->btn.cross << std::endl
      << "btnCircle: " << (uint32_t)obj->btn.circle << std::endl
      << "btnTriangle: " << (uint32_t)obj->btn.triangle << std::endl
      << "btnL1: " << (uint32_t)obj->btn.L1 << std::endl
      << "btnR1: " << (uint32_t)obj->btn.R1 << std::endl
      << "btnL2: " << (uint32_t)obj->btn.L2 << std::endl
      << "btnR2: " << (uint32_t)obj->btn.R2 << std::endl
      << "btnCreate: " << (uint32_t)obj->btn.create << std::endl
      << "btnOptions: " << (uint32_t)obj->btn.options << std::endl
      << "btnL3: " << (uint32_t)obj->btn.L3 << std::endl
      << "btnR3: " << (uint32_t)obj->btn.R3 << std::endl
      << "btnHome: " << (uint32_t)obj->btn.home << std::endl
      << "btnPad: " << (uint32_t)obj->btn.pad << std::endl
      << "btnMute: " << (uint32_t)obj->btn.mute << std::endl
      << "btnLeftFunction: " << (uint32_t)obj->btn.leftFunction << std::endl
      << "btnRightFunction: " << (uint32_t)obj->btn.rightFunction << std::endl
      << "btnLeftPaddle: " << (uint32_t)obj->btn.leftPaddle << std::endl
      << "btnRightPaddle: " << (uint32_t)obj->btn.rightPaddle << std::endl
      << "reserved: " << (uint32_t)obj->btn.reserved << std::endl
      << "\n-------------------\n"
      << std::endl
      << "gyroX: " << obj->gyro.x << std::endl
      << "gyroY: " << obj->gyro.y << std::endl
      << "gyroZ: " << obj->gyro.z << std::endl
      << "accelX: " << obj->accel.x << std::endl
      << "accelY: " << obj->accel.y << std::endl
      << "accelZ: " << obj->accel.z << std::endl
      << "sensorTimestamp: " << obj->sensorTimestamp << std::endl
      << "temperature: " << (int32_t)obj->temperature << std::endl
      << "\n-------------------\n"
      << std::endl
      << "finger1Index: " << (uint32_t)obj->tData.finger[0].index << std::endl
      << "finger1notTouch: " << (uint32_t)obj->tData.finger[0].notTouching
      << std::endl
      << "finger1X: " << (uint32_t)obj->tData.finger[0].fingerX << std::endl
      << "finger1Y: " << (uint32_t)obj->tData.finger[0].fingerY << std::endl
      << "finger2Index: " << (uint32_t)obj->tData.finger[1].index << std::endl
      << "finger2notTouch: " << (uint32_t)obj->tData.finger[1].notTouching
      << std::endl
      << "finger2X: " << (uint32_t)obj->tData.finger[1].fingerX << std::endl
      << "finger2Y: " << (uint32_t)obj->tData.finger[1].fingerY << std::endl
      << "timestamp: " << (uint32_t)obj->tData.timestamp << std::endl
      << "\n-------------------\n"
      << std::endl
      << "rTriggerStopLocation: " << (uint32_t)obj->rTrig.stopLoc << std::endl
      << "rTriggerStatus: " << (uint32_t)obj->rTrig.status << std::endl
      << "lTriggerStopLocation: " << (uint32_t)obj->lTrig.stopLoc << std::endl
      << "lTriggerStatus: " << (uint32_t)obj->lTrig.status << std::endl
      << "hostTimestamp: " << (uint32_t)obj->hostTimestamp << std::endl
      << "rTrigEffect: " << (uint32_t)obj->rTrigEffect << std::endl
      << "lTrigEffect: " << (uint32_t)obj->lTrigEffect << std::endl
      << "\n-------------------\n"
      << std::endl
      << "deviceTimestamp: " << (uint32_t)obj->deviceTimeStamp << std::endl
      << "powerPercent: " << (uint32_t)obj->batteryCharge << std::endl
      << "powerState: " << (uint32_t)obj->batteryState << std::endl
      << "\n-------------------\n"
      << std::endl
      << "plugHeadphone: " << (uint32_t)obj->pDev.headphones << std::endl
      << "plugMic: " << (uint32_t)obj->pDev.mic << std::endl
      << "micMuted: " << (uint32_t)obj->pDev.micMuted << std::endl
      << "plugUSBData: " << (uint32_t)obj->pDev.USB_Data << std::endl
      << "plugUSBPower: " << (uint32_t)obj->pDev.USB_Power << std::endl
      << "reserved: " << (uint32_t)obj->pDev.reserved << std::endl
      << "plugExternalMic: " << (uint32_t)obj->externalMic << std::endl
      << "hapticLowPassFilter: " << (uint32_t)obj->hapticLowPassFilter
      << std::endl
      << "reserved: " << (uint32_t)obj->reserved2 << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[0] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[1] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[2] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[3] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[4] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[5] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[6] << std::endl
      << "aesCmac: " << (uint32_t)obj->aesCmac[7] << std::endl
      << "\n-------------------\n"
      << std::endl;
}

void batteryCharge(dualsense *ds) {
  int retval = -1;
  uint8_t data[DS_INPUT_REPORT_BT_SIZE];
  int res = hid_read_timeout(ds->dev, data, sizeof(data), DS_READ_TIMEOUT);

  if (res <= 0) {
    if (res == 0)
      fprintf(stderr, "Timeout waiting for report\n");
    else
      fprintf(stderr, "Failed to read report %ls\n", hid_error(ds->dev));

    return;
  }

  USBGetStateData *ds_report;

  if ((ds->connection == CONTROLLER_WIRE) && (data[0] == DS_INPUT_REPORT_USB) &&
      (res == DS_INPUT_REPORT_USB_SIZE)) {
    ds_report = (USBGetStateData *)&data[1];
  } else if ((ds->connection == CONTROLLER_BT) &&
             (data[0] == DS_INPUT_REPORT_BT) &&
             (res == DS_INPUT_REPORT_BT_SIZE)) {
    ds_report = (USBGetStateData *)&data[2];
  } else {
    fprintf(stderr, "Unhandled report ID %d\n", (int)data[0]);
    return;
  }
  const char *battery_status;
  uint8_t battery_capacity;
  uint8_t battery_data = ds_report->batteryCharge;
  powerState charging_status = ds_report->batteryState;

  if (charging_status == COMPLETE)
    battery_capacity = 100;
  else
    battery_capacity = MIN(battery_data * 10 + 5, 100);

  ds->battery.type = charging_status;
  ds->battery.currentCharge = battery_capacity;

  return;
}
