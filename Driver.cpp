// Driver.cpp
#include "Driver.h"

Driver::Driver(int directionPin, int stepPin) {
  _directionPin =     directionPin;
  _stepPin =          stepPin;
  _stepTimeInterval = DEFAULT_STEP_TIME_INTERVAL;
  _target =           DEFAULT_INITIAL_TARGET;
  _halfDeadZone =     DEFAULT_HALF_DEAD_ZONE;
  _skipStepAfterDirectionChangeCounter = 0;

  pinMode(_directionPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  digitalWrite(_directionPin, LOW);
  digitalWrite(_stepPin, LOW);

  _lastStepTime = millis();
}

void Driver::setDirection(float instantValue) {
  int oldDirectionValue = digitalRead(_directionPin);
  int newDirectionValue = (instantValue > _target) ? HIGH : LOW;
  if (oldDirectionValue != newDirectionValue) {
    digitalWrite(_directionPin, newDirectionValue);
    _skipStepAfterDirectionChangeCounter = 2;
  }
}

void Driver::toggleStep() {
  digitalWrite(_stepPin, !digitalRead(_stepPin));
}    

bool Driver::isInsideDeadZone(float instantValue) {
    return ((instantValue > (_target - _halfDeadZone)) && (instantValue < (_target + _halfDeadZone)));
}

void Driver::step(float instantValue) {
  unsigned long instantTime = millis();

  // Если с прошлого шага прошло меньше рабочего интервала - пропустить
  if ((instantTime - _lastStepTime) < _stepTimeInterval)
    return;

  // Если надо пропустить шаг после смены направления - пропустить
  if (_skipStepAfterDirectionChangeCounter-- > 0) {
    return;
  }

  // Если внутри мертвой зоны - пропустить шаг
  if (isInsideDeadZone(instantValue))
    return;

  setDirection(instantValue);
  toggleStep();
  _lastStepTime = instantTime;
}
