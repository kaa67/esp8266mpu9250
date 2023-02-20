// Driver.h
#ifndef Driver_h
#define Driver_h

#include <Arduino.h>

#define DEFAULT_STEP_TIME_INTERVAL 1
#define DEFAULT_INITIAL_TARGET 0.0
#define DEFAULT_HALF_DEAD_ZONE 0.01

class Driver {
  private:
    int _directionPin; // пин для направления вращения степпера
    int _stepPin; // пин для шаговых сигналов степпера

    int _stepTimeInterval; // (ms) время между сменой уровня на пине шага
    unsigned long _lastStepTime; // (ms) врeмя последней операции смены шага
    int _skipStepAfterDirectionChangeCounter; // отсрочка шага на неск loop

    float _target; // (g) куда крутить будем
    float _halfDeadZone; // Мертвая зона для формирования сектора покоя [t-h .. t+h] , по умолчанию 0.01

    void setDirection(float instantValue);
    void toggleStep();
    bool isInsideDeadZone(float instantValue);

  public: 
    Driver(int directionPin, int stepPin);
    void step(float instantValue);
};

#endif