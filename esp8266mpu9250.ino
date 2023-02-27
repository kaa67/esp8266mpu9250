#include <MPU6500_WE.h>
#include <Wire.h>

#include "SkipVibrations.h"
#include "Observation.h"
#include "Driver.h"
#include "HorizonZeroDown.h"

MPU6500_WE mpu6500 = MPU6500_WE(MPU6500_ADDR);

Driver x = Driver(X_DIRECTION_PIN, X_STEP_PIN);
Driver y = Driver(Y_DIRECTION_PIN, Y_STEP_PIN);

SkipVibrations skipVibrations = SkipVibrations();
Observation observation = Observation(& mpu6500);
HorizonZeroDown horizonZeroDown = HorizonZeroDown(& x, & y);

enum { START, SKIP_VIBRATIONS, OBSERVATION, HORIZON_ZERO_DOWN } stage;

void setup() {
  Wire.begin();
  mpu6500.init();
  mpu6500.setSampleRateDivider(5);

  stage = START;
}

void loop() {
  switch(stage) {
    case SKIP_VIBRATIONS:
      if (skipVibrations.isComplete()) {
        observation.start();
        stage = OBSERVATION;
      };
      break;
    case OBSERVATION:
      if (observation.isComplete()) {
        horizonZeroDown.start(observation.getValues());
        stage = HORIZON_ZERO_DOWN;
      }
      break;
    default:
      if (horizonZeroDown.isComplete()) {
        skipVibrations.start();
        stage = SKIP_VIBRATIONS;
      }
  }
}
