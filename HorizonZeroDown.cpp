#include "HorizonZeroDown.h"

HorizonZeroDown::HorizonZeroDown(Driver * x, Driver * y) : _x(x), _y(y) {}

bool HorizonZeroDown::isComplete() {
  return _x->isComplete() && _y->isComplete();
  return true;
}

void HorizonZeroDown::start(xyzFloat values) {
  int xDirection = (values.x < 0) ? LOW : HIGH;
  int yDirection = (values.y < 0) ? LOW : HIGH;

  int xStepsCount = abs((int)(50. * values.x)) + 1;
  int yStepsCount = abs((int)(50. * values.x)) + 1;

  _x->start(xDirection, xStepsCount);
  _y->start(yDirection, yStepsCount);
}
