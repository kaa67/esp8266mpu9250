#include <MPU6500_WE.h>
#include <Wire.h>

#include "Driver.h"

#define MPU6500_ADDR 0x68

#define XDirectionPin D5
#define XStepPin D6
#define YDirectionPin D7
#define YStepPin D8

MPU6500_WE myMPU6500 = MPU6500_WE(MPU6500_ADDR);

Driver xDriver = Driver(XDirectionPin, XStepPin);
Driver yDriver = Driver(YDirectionPin, YStepPin);

xyzFloat gValue;
unsigned long lastObservationTime;

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin();
  if(!myMPU6500.init()){
    Serial.println("MPU6500 does not respond");
  }
  else{
    Serial.println("MPU6500 is connected");
  }
  
  // Serial.println("Position you MPU6500 flat and don't move it - calibrating...");
  // delay(1000);
  // myMPU6500.autoOffsets();
  // Serial.println("Done!");
  
  // myMPU6500.enableGyrDLPF();
  // myMPU6500.setGyrDLPF(MPU6500_DLPF_1); // У нас примерно 125гц (4мс + 4мс - Период мотора) kolosoft
  myMPU6500.setSampleRateDivider(5);
  // myMPU6500.setGyrRange(MPU6500_GYRO_RANGE_250);
  // myMPU6500.setAccRange(MPU6500_ACC_RANGE_2G);
  // myMPU6500.enableAccDLPF(true);
  // myMPU6500.setAccDLPF(MPU6500_DLPF_1); // У нас примерно 125гц (4мс + 4мс - Период мотора) kolosoft
  delay(200);
  gValue = myMPU6500.getGValues();
  lastObservationTime = millis();
}

void loop() {
  unsigned long newObservationTime = millis();
  if ((newObservationTime - lastObservationTime) > 5) {
    gValue = myMPU6500.getGValues();
    lastObservationTime = newObservationTime;
  }
  // float resultantG = myMPU6500.getResultantG(gValue);

  // if (gValue.x >= 0) {
  //   Serial.print("+");
  // }
  // Serial.print(gValue.x);
  // Serial.print(" ");

  // if (gValue.y >= 0) {
  //   Serial.print("+");
  // }
  // Serial.print(gValue.y);
  // Serial.println(" ");

  xDriver.step(gValue.x);
  yDriver.step(gValue.y);
}
