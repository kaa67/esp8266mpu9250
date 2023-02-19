// Driver.cpp
#include "Driver.h"

Driver::Driver(int directionPin, int stepPin) {
  _directionPin =     directionPin;
  _stepPin =          stepPin;
  _stepTimeInterval = DEFAULT_STEP_TIME_INTERVAL;
  _target =           DEFAULT_INITIAL_TARGET;
  _halfDeadZone =     DEFAULT_HALF_DEAD_ZONE;

  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  _lastStepTime = millis();
}

Driver::Driver(int directionPin, int stepPin, int stepTimeInterval, float initialTarget, float halfDeadZone) {
  _directionPin =     directionPin;
  _stepPin =          stepPin;
  _stepTimeInterval = stepTimeInterval;
  _target =           initialTarget;
  _halfDeadZone =     halfDeadZone;

  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  _lastStepTime = millis();
}

void Driver::setDirection(float instantValue) {
  digitalWrite(_directionPin, instantValue > _target);
}

void Driver::toggleStep() {
  digitalWrite(_stepPin, !digitalRead(_stepPin));
}    

void Driver::setTarget(float target) {
  _target = target;
}

void Driver::step(float instantValue) {
  unsigned long instantTime = millis();

  // пора ли?
  if ((instantTime - _lastStepTime) < _stepTimeInterval)
    return;

  // Не мертвая зона ли?
  float minHalfDeadZone = _target - _halfDeadZone;
  float maxHalfDeadZone = _target + _halfDeadZone;

  if ((instantValue > minHalfDeadZone) && (instantValue < maxHalfDeadZone))
    return;

  // Океюшки, интервал превышен параметр вне мертвой зоны, шагнуть
  setDirection(instantValue);
  toggleStep();
  _lastStepTime = instantTime;
}
