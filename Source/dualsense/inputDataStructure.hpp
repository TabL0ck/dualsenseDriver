#include <cstdint>

typedef enum direction : uint8_t {
  NORTH = 0,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST,
  NONE
} DPad;

/** @struct stick
 *  @brief
 *    This structure handle stick position
 *  @var stick::x
 *    Member 'x' is current stick state in x-axis
 *  @var stick::y
 *    Member 'y' is current stick state in y-axis
 */
typedef struct stick_t {
  uint8_t x;
  uint8_t y;
} stick;

/** @struct trigger
 *  @brief
 *    This structure handle trigger state
 *  @var trigger::left
 *    Member 'left' is state of left trigger
 *  @var trigger::right
 *    Member 'right' is state of right trigget
 */
typedef struct trigger_t {
  uint8_t left;
  uint8_t right;
} trigger;

typedef struct buttons_t {
  direction DPad : 4;
  uint8_t square : 1;
  uint8_t cross : 1;
  uint8_t circle : 1;
  uint8_t triangle : 1;
  uint8_t L1 : 1;
  uint8_t R1 : 1;
  uint8_t L2 : 1;
  uint8_t R2 : 1;
  uint8_t create : 1;
  uint8_t options : 1;
  uint8_t L3 : 1;
  uint8_t R3 : 1;
  uint8_t home : 1;
  uint8_t pad : 1;
  uint8_t mute : 1;
  uint8_t leftFunction : 1;
  uint8_t rightFunction : 1;
  uint8_t leftPaddle : 1;
  uint8_t rightPaddle : 1;
  uint8_t reserved : 1;
} buttons;

typedef struct angularVelocity_t {
  int16_t x;
  int16_t y;
  int16_t z;
} angularVelocity;

typedef struct accelerometer_t {
  int16_t x;
  int16_t y;
  int16_t z;
} accelerometer;

typedef struct USBGetStateData_t {
  stick lStick;
  stick rStick;
  trigger trig;
  uint8_t seqNo;
  buttons btn;
  uint8_t reserved[5];
  angularVelocity gyro;
  accelerometer accel;
} USBGetStateData;
