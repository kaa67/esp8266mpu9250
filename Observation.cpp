#include "Observation.h"

Observation::Observation(MPU6500_WE * mpu6500) : _mpu(mpu6500) {
  counter = 0;
  values.x = 0.0;
  values.y = 0.0;
  values.z = 0.0;
}

void Observation::start() {
  counter = OBSERVATION_COUNT;
  values.x = 0.0;
  values.y = 0.0;
  values.z = 0.0;
}
      
bool Observation::isComplete() {
  if (counter < 1) return true;

  if (counter > 0) {
    values += _mpu->getGValues();
  }

  counter--;

  if (counter < 1) {
    values /= OBSERVATION_COUNT;
  }

  return counter < 1;
}

xyzFloat Observation::getValues() {
  return _mpu->getGValues();
}
