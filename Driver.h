#ifndef Driver_h
  #define Driver_h

  #include <Arduino.h>

  #include "config.h"

  class Driver {
    private:
      int _directionPin;
      int _stepPin;
      int _stepsCounter;
      unsigned long _lastStepTime;

    public: 
      Driver(int directionPin, int stepPin);
      bool isComplete();
      void start(int direction, int stepsCount);
  };

#endif
