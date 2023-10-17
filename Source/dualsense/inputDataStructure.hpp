#include <cstdint>
#pragma pack(1)
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

/** @struct buttons
 *  @brief
 *    Contain state of all controller buttons
 *  @var buttons:DPad
 *    Member 'DPad' return state from crosses
 *  @var buttons:square
 *    Member 'square' return state from []-button
 *  @var buttons:cross
 *    Member 'cross' return state from X-button
 *  @var buttons:circle
 *    Member 'circle' return state from O-button
 *  @var buttons:triangle
 *    Member 'triangle' return state from /\-button
 *  @var buttons:L1
 *    Member 'L1' return state from left shoulder
 *  @var buttons:R1
 *    Member 'R1' return state from right shoulder
 *  @var buttons:L2
 *    Member 'L2' return state from left trigger
 *  @var buttons:R2
 *    Member 'R2' return state from right trigger
 *  @var buttons:create
 *    Member 'create' return state from create button
 *  @var buttons:options
 *    Member 'options' return state from options button
 *  @var buttons:L3
 *    Member 'L3' return state from pressed on left stick
 *  @var buttons:R3
 *    Member 'R3' return state from pressed on right stick
 *  @var buttons:home
 *    Member 'home' return state from pressed on home button
 *  @var buttons:pad
 *    Member 'pad' return state from pressed on pad button
 *  @var buttons:mute
 *    Member 'mute' return state from pressed on mute button
 *  @var buttons:leftFunction
 *    Member 'leftFunction' ?????????
 *  @var buttons:rightFunction
 *    Member 'rightFunction' ????????
 *  @var buttons:leftPaddle
 *    Member 'leftPaddle' ?????????
 *  @var buttons:rightPaddle
 *    Member 'rightPaddle' ?????????
 *  @var buttons:reserved
 *    Member 'reserved' reserved bit
 */
typedef struct buttons_t {
  direction DPad : 4;
  uint8_t square : 1;
  uint8_t cross : 1;
  uint8_t circle : 1;
  uint8_t triangle : 1; /*1 bytes*/
  uint8_t L1 : 1;
  uint8_t R1 : 1;
  uint8_t L2 : 1;
  uint8_t R2 : 1;
  uint8_t create : 1;
  uint8_t options : 1;
  uint8_t L3 : 1;
  uint8_t R3 : 1; /*2 bytes*/
  uint8_t home : 1;
  uint8_t pad : 1;
  uint8_t mute : 1;
  uint8_t leftFunction : 1;
  uint8_t rightFunction : 1;
  uint8_t leftPaddle : 1;
  uint8_t rightPaddle : 1;
  uint8_t reserved : 1; /*3 bytes*/
} buttons;

/** @struct angularVelocity
 *  @brief
 *    Data from gyroscope sensor
 *  @angularVelocity:x
 *    Member 'x' is data from sensor for x-axis
 *  @angularVelocity:y
 *    Member 'y' is data from sensor for y-axis
 *  @angularVelocity:z
 *    Member 'z' is data from sensor for z-axis
 */
typedef struct angularVelocity_t {
  int16_t x;
  int16_t y;
  int16_t z;
} angularVelocity;

/** @struct accelerometer
 *  @brief
 *    Data from accelerometer sensor
 *  @accelerometer:x
 *    Member 'x' is data from sensor for x-axis
 *  @accelerometer:y
 *    Member 'y' is data from sensor for y-axis
 *  @accelerometer:z
 *    Member 'z' is data from sensor for z-axis
 */
typedef struct accelerometer_t {
  int16_t x;
  int16_t y;
  int16_t z;
} accelerometer;

/** @struct touchFingerData
 *  @brief
 *    Data from sensor panel for 1 finger
 *  @var touchFingerData:index
 *    Member 'index' is touch index
 *  @var touchFingerData:notTouching
 *    Member 'notTouching' ???????
 *  @var touchFingerData:fingerX
 *    Member 'fingerX' is x-position of finger
 *  @var touchFingerData:fingerY
 *    Member 'fingerY' is y-position of finger
 */
typedef struct touchFingerData_t {
  uint32_t index : 7;
  uint32_t notTouching : 1; /*1 bytes*/
  uint32_t fingerX : 12;
  uint32_t fingerY : 12; /*4 bytes*/
} touchFingerData;

/** @struct touchData
 *  @brief
 *    Contains data from sensors panel
 *  @var touchData:finger
 *    Member 'finger' contain data about state each finger on panel
 *  @var touchData:timestamp
 *    Member 'timestamp' is current time
 */
typedef struct touchData_t {
  touchFingerData finger[2]; /*8 bytes*/
  uint8_t timestamp;         /*9 bytes*/
} touchData;

/** @struct triggerStatus
 *  @brief
 *    Contain current settings of trigger
 *  @var triggerStatus:stopLoc
 *    Member 'stopLoc' is last position where trigger stay activated
 *  @var triggerStatus:status
 *    Member 'status' is current feedback state of trigger
 */
typedef struct triggerStatus_t {
  uint8_t stopLoc : 4;
  uint8_t status : 4;
} triggerStatus;

/** @struct pluggedDevices
 *  @brief
 *    State of additional devices
 *  @var pluggedDevices:headphones
 *    Member 'headphones' is flag which indicates connected headphones
 *    to controller
 *  @var pluggedDevices:mic
 *    Member 'mic' is flag which indicates connected microphone
 *    to controller
 *  @var pluggedDevices:micMuted
 *    Member 'micMuted' is flag which indicates ative microphone or not
 *  @var pluggedDevices:USB_Data
 *    Member 'USB_Data' is flag which indicates connection D- and D+
 *    pins of USB-TypeC connected to external device
 *  @var pluggedDevices:USB_Power
 *    Member 'USB_Power' is flag which indicates connection controller
 *    to external power supply
 *  @var pluggedDevices:reserved
 *    Member 'reserved' is reserved
 */
typedef struct pluggedDevices_t {
  uint8_t headphones : 1;
  uint8_t mic : 1;
  uint8_t micMuted : 1;
  uint8_t USB_Data : 1;
  uint8_t USB_Power : 1;
  uint8_t reserved : 3;
} pluggedDevices;

typedef struct USBGetStateData_t {
  stick lStick;             /*2 bytes*/
  stick rStick;             /*4 bytes*/
  trigger trig;             /*6 bytes*/
  uint8_t seqNo;            /*7 bytes*/
  buttons btn;              /*10 bytes*/
  uint8_t reserved[5];      /*15 bytes*/
  angularVelocity gyro;     /*21 bytes*/
  accelerometer accel;      /*27 bytes*/
  uint32_t sensorTimestamp; /*31 bytes*/
  int8_t temperature;       /*32 bytes*/
  touchData tData;          /*41 bytes*/
  triggerStatus rTrig;      /*42 bytes*/
  triggerStatus lTrig;      /*43 bytes*/
  uint32_t hostTimestamp;   /*47 bytes*/
  uint8_t rTrigEffect : 4;
  uint8_t lTrigEffect : 4;  /*48 bytes*/
  uint32_t deviceTimeStamp; /*52 bytes*/
  uint8_t batteryCharge : 4;
  powerState batteryState : 4; /*53 bytes*/
  pluggedDevices pDev;         /*54 bytes*/
  uint8_t externalMic : 1;
  uint8_t hapticLowPassFilter : 1;
  uint8_t reserved2 : 6; /*55 bytes*/
  uint8_t aesCmac[8];    /*63 bytes*/
} USBGetStateData;
