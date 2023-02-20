// Driver.cpp
#include "Driver.h"

Driver::Driver(int directionPin, int stepPin, int speedPin) {
  _directionPin =     directionPin;
  _stepPin =          stepPin;
  _speedPin =         speedPin;
  _stepTimeInterval = DEFAULT_STEP_TIME_INTERVAL;
  _target =           DEFAULT_INITIAL_TARGET;
  _halfDeadZone =     DEFAULT_HALF_DEAD_ZONE;

  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  pinMode(_speedPin, OUTPUT);
  _lastStepTime = millis();
}

void Driver::setDirection(float instantValue) {
  digitalWrite(_directionPin, instantValue > _target);
}

void Driver::toggleStep() {
  digitalWrite(_stepPin, !digitalRead(_stepPin));
}    

void Driver::setSpeed(int level) {
  digitalWrite(_speedPin, level);
}

void Driver::setTarget(float target) {
  _target = target;
}

void Driver::step(float instantValue) {
  unsigned long instantTime = millis();

  // пора ли?
  if ((instantTime - _lastStepTime) < _stepTimeInterval)
    return;

  float minHalfDeadZone = _target - _halfDeadZone;
  float maxHalfDeadZone = _target + _halfDeadZone;
  // 1  это 1/4 скорости, 0 - полная скорость
  int speed = (instantValue > minHalfDeadZone) && (instantValue < maxHalfDeadZone);

  // Океюшки, интервал превышен параметр вне мертвой зоны, шагнуть
  // setSpeed(speed);
  setSpeed(0);
  setDirection(instantValue);
  toggleStep();
  _lastStepTime = instantTime;
}
