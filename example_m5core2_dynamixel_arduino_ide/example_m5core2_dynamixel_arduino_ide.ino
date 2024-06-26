#include <Dynamixel2Arduino.h>
#include <M5Unified.h>

#define DEBUG_SERIAL Serial
HardwareSerial& DXL_SERIAL = Serial1;
Dynamixel2Arduino dxl;

// M5Stack Core2 PORT A
const uint8_t RX_SERVO = 32;
const uint8_t TX_SERVO = 33;

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;

using namespace ControlTableItem;

void setup() {

  DXL_SERIAL.begin(57600, SERIAL_8N1, RX_SERVO, TX_SERVO);
  dxl = Dynamixel2Arduino(DXL_SERIAL);

  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Display.println("DYNAMIXEL TTL");
  M5.Display.println("");
  M5.Display.println("Velocity Mode Example");
  M5.Display.println("");
  M5.Display.println("Initializing...");
  DEBUG_SERIAL.begin(115200);

  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.ping(DXL_ID);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_VELOCITY);
  dxl.torqueOn(DXL_ID);
}


void loop() {

  // Reset display
  M5.Display.clear();
  M5.Display.setCursor(0, 0);

  // Set Goal Velocity using RPM
  dxl.setGoalVelocity(DXL_ID, 60, UNIT_RPM);
  delay(1000);

  int rpm = dxl.getPresentVelocity(DXL_ID, UNIT_RPM);

  DEBUG_SERIAL.print("Target Velocity(rpm): 60");
  DEBUG_SERIAL.print("Present Velocity(rpm) : ");
  DEBUG_SERIAL.println(rpm);
  M5.Display.println("DYNAMIXEL TTL");
  M5.Display.println("Target Velocity(rpm): 60");
  M5.Display.print("Present Velocity(rpm) : ");
  M5.Display.println(rpm);
  M5.Display.println("");
  delay(1000);

  dxl.setGoalVelocity(DXL_ID, -60, UNIT_RPM);
  delay(1000);

  rpm = dxl.getPresentVelocity(DXL_ID, UNIT_RPM);
  DEBUG_SERIAL.println("Target Velocity(rpm): -60");
  DEBUG_SERIAL.print("Present Velocity(rpm): ");
  DEBUG_SERIAL.println(rpm);

  M5.Display.println("DYNAMIXEL TTL");
  M5.Display.println("Target Velocity(rpm): -60");
  M5.Display.print("Present Velocity(rpm): ");
  M5.Display.println(rpm);
  M5.Display.println("");
  delay(1000);
}
