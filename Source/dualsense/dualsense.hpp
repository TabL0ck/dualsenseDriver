#ifndef DUALSENSE_HPP
#define DUALSENSE_HPP
/*Include standart libs*/
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <hidapi/hidapi.h>
#include <iostream>
/*Include external libs*/
#include "utils.hpp"

/*Define device VID&PID*/
#define DS_VID 0x054C
#define DS_PID 0x0CE6

/** @enum dualsenseConnType
 *  @brief
 *    Enum with types of dualsense connection
 *  @param CONTROLLER_DISCONNECTED
 *    Device is disconnected
 *  @param CONTROLLER_BT
 *    Device is connected via bluetooth
 *  @param CONTROLLER_WIRE
 *    Device is connected via wire
 */
typedef enum dualsenseConnType_t {
  CONTROLLER_DISCONNECTED = 0,
  CONTROLLER_BT,
  CONTROLLER_WIRE
} dualsenseConnType;

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
  dualsenseConnType connection;
  hid_device *dev;
  char MAC_address[18];
  uint8_t output_seq;
} dualsense;

/**
 * Initialization of dualsense device
 * @param ds pointer to dualsense struct object
 * @param serial number of current connected devices
 * @ret state of dualsense connection
 */
bool dualsense_init(dualsense *ds, const char *serial);

/**
 * Return connections state
 * @param ds pointer to dualsense struct object
 * @ret current connection state of dualsense
 */
bool check_connection(dualsense *ds);
#endif
