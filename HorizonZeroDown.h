#ifndef HorizonZeroDown_h
  #define HorizonZeroDown_h

  #include <Arduino.h>
  #include "config.h"
  #include "Driver.h"

  Driver x = Driver(X_DIRECTION_PIN, X_STEP_PIN);
  Driver y = Driver(Y_DIRECTION_PIN, Y_STEP_PIN);

  class HorizonZeroDown {
    public: 
      HorizonZeroDown();
      bool isComplete();
      void start(xyzFloat);
  };

#endif