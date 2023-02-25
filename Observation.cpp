#include "Observation.h"

Observation::Observation() {
  mpu6500.init();
  mpu6500.setSampleRateDivider(5);
  counter = 0;
  values.x = 0.f;
  values.y = 0.f;
  values.z = 0.f;
}

void Observation::start() {
  counter = OBSERVATION_COUNT;
  values.x = 0.f;
  values.y = 0.f;
  values.z = 0.f;
}
      
bool Observation::isComplete() {
  if (counter < 1) return true;

  if (counter > 0) {
    values += mpu6500.getGValues();
  }

  counter--;

  if (counter < 1) {
    values /= OBSERVATION_COUNT;
  }

  return counter < 1;
}

xyzFloat Observation::getValues() {
  xyzFloat temp{0.f, 0.f, 0.f};
  return temp;
}
