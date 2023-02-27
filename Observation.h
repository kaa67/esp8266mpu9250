#ifndef Observation_h
  #define Observation_h

  #include <MPU6500_WE.h>

  #include "config.h"

  class Observation {
    private:
      MPU6500_WE * _mpu;
      int  counter;
      xyzFloat values;

    public: 
      Observation(MPU6500_WE *);
      void start();
      bool isComplete();
      xyzFloat getValues();
  };

#endif
