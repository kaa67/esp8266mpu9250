void observationStart() {
  _observationCounter = OBSERVATION_COUNT;
  _observationValues.x = 0.f;
  _observationValues.y = 0.f;
  _observationValues.z = 0.f;
};
      
bool observationIsComplete() {
  if (_observationCounter < 1) return true;

  if (_observationCounter > 0) {
    _observationValues += mpu6500.getGValues();
  }

  _observationCounter--;

  if (_observationCounter < 1) {
    _observationValues /= OBSERVATION_COUNT;
  }

  return _observationCounter < 1;
};
