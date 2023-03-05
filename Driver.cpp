#include "Driver.h"

Driver::Driver(int directionPin, int stepPin) {
  _directionPin = directionPin;
  _stepPin = stepPin;
  _stepsCounter = 0;
  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
}

void Driver::start(int direction, int stepsCount) {
  _stepsCounter = stepsCount;
  digitalWrite(_directionPin, direction);
  _lastStepTime = micros();
}

bool Driver::isComplete() {
  if (_stepsCounter < 1) return true;

  unsigned long realTime = micros();

  if ((realTime - _lastStepTime) < DRIVER_STEP_TIME_INTERVAL) return false;

  digitalWrite(_stepPin, !digitalRead(_stepPin));
  _lastStepTime = realTime;
  _stepsCounter--;

  return _stepsCounter < 1;
}
