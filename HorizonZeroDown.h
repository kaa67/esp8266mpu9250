#ifndef HorizonZeroDown_h
  #define HorizonZeroDown_h

  #include <Arduino.h>
  #include <MPU6500_WE.h>

  #include "Driver.h"
 
  class HorizonZeroDown {
    private:
      Driver * _x;
      Driver * _y;

    public: 
      HorizonZeroDown(Driver *, Driver *);
      bool isComplete();
      void start(xyzFloat);
  };

#endif