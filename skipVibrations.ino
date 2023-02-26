bool skipVibrationsIsComplete() {
  return (millis() - _skipVibrationsStartTime) > SKIP_VIBRATION_INTERVAL;
}

void skipVibrationsStart() {
  _skipVibrationsStartTime = millis();
}
