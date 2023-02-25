#ifndef SkipVibrations_h
  #define SkipVibrations_h

  #include <Arduino.h>
  #include "config.h"
  
  class SkipVibrations {
    private:
      unsigned long startTime;

    public: 
      SkipVibrations();
      bool isComplete();
      void start();
  };

#endif
