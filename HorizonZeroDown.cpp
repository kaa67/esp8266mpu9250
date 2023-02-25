#include "HorizonZeroDown.h"

HorizonZeroDown::HorizonZeroDown() {}

bool HorizonZeroDown::isComplete() {
  return x.isComplete() && y.isComplete();
}

void HorizonZeroDown::start(xyzFloat values) {
  int xDirection = (values.x < 0) ? LOW : HIGH;
  int yDirection = (values.y < 0) ? LOW : HIGH;

  int xStepsCount = abs((int)(50. * values.x)) + 1;
  int yStepsCount = abs((int)(50. * values.x)) + 1;

  x.start(xDirection, xStepsCount);
  y.start(yDirection, yStepsCount);
}
