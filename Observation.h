#ifndef Observation_h
  #define Observation_h

  #include <MPU6500_WE.h>
  #include "config.h"

  MPU6500_WE mpu6500 = MPU6500_WE(MPU6500_ADDR);

  class Observation {
    private:
      int  counter;
      xyzFloat values;

    public: 
      Observation();
      void start();
      bool isComplete();
      xyzFloat getValues();
  };

#endif
