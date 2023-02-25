#include "SkipVibrations.h"

SkipVibrations::SkipVibrations() {
  startTime = 0;
}

void SkipVibrations::start() {
  startTime = millis();
}    

bool SkipVibrations::isComplete() {
  return (millis() - startTime) > SKIP_VIBRATION_INTERVAL;
}
