#include <MPU6500_WE.h>
#include <Wire.h>

#define SKIP_VIBRATION_INTERVAL 30
#define MPU6500_ADDR 0x68
#define OBSERVATION_COUNT 10
#define X_DIRECTION_PIN D5
#define X_STEP_PIN D6
#define Y_DIRECTION_PIN D7
#define Y_STEP_PIN D8
#define DRIVER_STEP_TIME_INTERVAL 1

class Driver {
  private:
    int _directionPin;
    int _stepPin;
    int _stepsCounter;
    unsigned long _lastStepTime;

  public: 
    Driver(int directionPin, int stepPin) {
      _directionPin = directionPin;
      _stepPin =      stepPin;
      _stepsCounter = 0;

      pinMode(_directionPin, OUTPUT);
      pinMode(_stepPin, OUTPUT);
    }

    void start(int direction, int stepsCount) {
      _stepsCounter = stepsCount;
      digitalWrite(_directionPin, direction);
      _lastStepTime = millis();
    }

    bool isComplete() {
      if (_stepsCounter < 1) return true;

      unsigned long realTime = millis();

      if ((realTime - _lastStepTime) < DRIVER_STEP_TIME_INTERVAL) return false;

      digitalWrite(_stepPin, !digitalRead(_stepPin));
      _lastStepTime = realTime;
      _stepsCounter--;

      return _stepsCounter < 1;
    }
};

unsigned long _skipVibrationsStartTime;
int  _observationCounter;
xyzFloat _observationValues{ 0.f, 0.f, 0.f };

MPU6500_WE mpu6500 = MPU6500_WE(MPU6500_ADDR);
Driver x = Driver(X_DIRECTION_PIN, X_STEP_PIN);
Driver y = Driver(Y_DIRECTION_PIN, Y_STEP_PIN);

enum { SKIP_VIBRATIONS, OBSERVATION, HORIZON_ZERO_DOWN } stage;

void setup() {
  _skipVibrationsStartTime = millis();

  _observationCounter = 0;
  _observationValues.x = 0.0;
  _observationValues.y = 0.0;
  _observationValues.z = 0.0;

  Wire.begin();
  mpu6500.init();
  mpu6500.setSampleRateDivider(5);

  skipVibrationsStart();
  stage = SKIP_VIBRATIONS;
}

void loop() {
  switch(stage) {
    case SKIP_VIBRATIONS:
      if (skipVibrationsIsComplete()) {
        observationStart();
        stage = OBSERVATION;
      };
      break;
    case OBSERVATION:
      if (observationIsComplete()) {
        horizonZeroDownStart();
        stage = HORIZON_ZERO_DOWN;
      }
      break;
    case HORIZON_ZERO_DOWN:
    default:
      if (horizonZeroDownIsComplete()) {
        skipVibrationsStart();
        stage = SKIP_VIBRATIONS;
      }
  }
}
