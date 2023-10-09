#ifndef DUALSENSE_HPP
#define DUALSENSE_HPP
/*Include standart libs*/
#include <cstdint>
#include <cstring>
#include <hidapi/hidapi.h>
#include <iostream>
/*Include external libs*/

/*Define device VID&PID*/
#define DS_VID 0x054C
#define DS_PID 0x0CE6

/** @struct dualsense
 *  @brief
 *    This structure handle dualsense HID device
 *  @var dualsense::bluetooth_connect
 *    Member 'bluetooth_connect' contains type
 *    connection of dualsense
 *  @var dualsense::dev
 *    Member 'dev' contains pointer to HID device
 *  @var dualsense::MAC_address
 *    Member 'MAC_address' contains MAC of current device
 *  @var dualsense::output_seq
 *    Member 'output_seq' contains sequence number that need
 *    to be increased after each packet transfer
 */
typedef struct dualsense_t {
  bool bluetooth_connect;
  hid_device *dev;
  char MAC_address[18];
  uint8_t output_seq;
} dualsense;

/**
 * Initialization of dualsense device
 * @param ds pointer to dualsense struct object
 * @param serial number of current connected devices
 */
bool dualsense_init(dualsense *ds, const char *serial);
#endif
