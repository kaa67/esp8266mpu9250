#include <MPU6500_WE.h>
#include <Wire.h>

#include "SkipVibrations.h"
#include "Observation.h"
#include "HorizonZeroDown.h"

SkipVibrations skipVibrations = SkipVibrations();
Observation observation = Observation();
HorizonZeroDown horizonZeroDown = HorizonZeroDown();

enum { SKIP_VIBRATIONS, OBSERVATION, HORIZON_ZERO_DOWN } stage;

void setup() {
  Wire.begin();
  skipVibrations.start();
  stage = SKIP_VIBRATIONS;
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
        xyzFloat values = observation.getValues();
        horizonZeroDown.start(values);
        stage = HORIZON_ZERO_DOWN;
      }
      break;
    case HORIZON_ZERO_DOWN:
    default:
      if (horizonZeroDown.isComplete()) {
        skipVibrations.start();
        stage = SKIP_VIBRATIONS;
      }
  }
}
