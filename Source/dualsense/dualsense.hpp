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
#include "inputDataStructure.hpp"
#include "utils.hpp"

/*Define device VID&PID*/
#define DS_VID 0x054C
#define DS_PID 0x0CE6

/*Input commands to dualsense*/
#define DS_READ_TIMEOUT 1000
#define DS_INPUT_REPORT_BT 0x31
#define DS_INPUT_REPORT_BT_SIZE 78

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
typedef enum dualsenseConnType_t : uint8_t {
  CONTROLLER_DISCONNECTED = 0,
  CONTROLLER_BT,
  CONTROLLER_WIRE
} dualsenseConnType;

/** @enum powerState
 *  @brief
 *    Enum with types of dualsense power state
 *  @param DISCHARGING
 *    Device discharhing
 *  @param CHARGING
 *    Device charging
 *  @param COMPLETE
 *    Device battery is full
 *  @param ABNORMAL_VOLTAGE
 *    Device voltage is out of range
 *  @param ABNORMAL_TEMPERATURE
 *    Device temperature is out of range
 *  @param CHARGING_ERROR
 *    Device can't charge due aparature error
 */
typedef enum powerState_t : uint8_t {
  DISCHARGING = 0x00,
  CHARGING = 0x01,
  COMPLETE = 0x02,
  ABNORMAL_VOLTAGE = 0x0A,
  ABNORMAL_TEMPERATURE = 0x0B,
  CHARGING_ERROR = 0x0F
} powerState;

/** @struct dualsenseBatteryState
 *  @brief
 *    This structure handle current battery state
 *  @var dualsenseBatteryState::type
 *    Member 'type' handle power state of device
 *  @var dualsenseBatteryState::currentCharge
 *    Member 'currentCharge' handle current battery charge
 *    in percent
 */
typedef struct dualsenseBatteryState_t {
  powerState type;
  int currentCharge;
} dualsenseBatteryState;

/** @struct dualsense
 *  @brief
 *    This structure handle dualsense HID device
 *  @var dualsense::connection
 *    Member 'connection' contains type
 *    connection of dualsense
 *  @var dualsense::dev
 *    Member 'dev' contains pointer to HID device
 *  @var dualsense::MAC_address
 *    Member 'MAC_address' contains MAC of current device
 *  @var dualsense::output_seq
 *    Member 'output_seq' contains sequence number that need
 *    to be increased after each packet transfer
 *  @var dualsense::battery
 *    Member 'battery' contains current charge state of device
 */
typedef struct dualsense_t {
  hid_device *dev;
  char MAC_address[18];
  uint8_t output_seq;
  dualsenseConnType connection;
  dualsenseBatteryState battery;
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

/**
 * Return battery state
 * @param ds pointer to dualsense struct object
 * @ret current battery charge
 */
int batteryCharge(dualsense *ds);
#endif
