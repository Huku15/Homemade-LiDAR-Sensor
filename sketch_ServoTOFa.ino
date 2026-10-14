#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cx_class.h>
#include <Servo.h>
#define DEV_I2C Wire
#define SerialPort Serial

VL53L4CX sensor_vl53l4cx_sat(&DEV_I2C, A1);
Servo pan;
Servo tilt;
int status;
int panPos = 0;
int tiltPos = 0;

void setup() {
  SerialPort.begin(115200);
  DEV_I2C.begin();
  sensor_vl53l4cx_sat.begin();
  sensor_vl53l4cx_sat.VL53L4CX_Off();
  sensor_vl53l4cx_sat.InitSensor(0x12);
  sensor_vl53l4cx_sat.VL53L4CX_StartMeasurement();
  pan.attach(9);
  tilt.attach(10, 500, 2500);
}

void loop() {
  for (panPos = 0; panPos <= 180; panPos += 1) {
    pan.write(panPos);
    for (tiltPos = 0; tiltPos <= 120; tiltPos += 1) {
      tilt.write(tiltPos);
      delay(50);

      VL53L4CX_MultiRangingData_t MultiRangingData;
      VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
      uint8_t NewDataReady = 0;
      do {
        status = sensor_vl53l4cx_sat.VL53L4CX_GetMeasurementDataReady(&NewDataReady);
      } while (!NewDataReady);
      if ((!status) && (NewDataReady != 0)) {
        status = sensor_vl53l4cx_sat.VL53L4CX_GetMultiRangingData(pMultiRangingData);
        if (status == 0) {
          status = sensor_vl53l4cx_sat.VL53L4CX_ClearInterruptAndStartMeasurement();
        }
      }
      int distance = pMultiRangingData->RangeData[0].RangeMilliMeter;
      Serial.print(panPos);
      Serial.print(",");
      Serial.print(tiltPos);
      Serial.print(",");
      Serial.println(distance);
    }
  }
}