bool horizonZeroDownIsComplete() {
  return x.isComplete() && y.isComplete();
}

void horizonZeroDownStart() {
  int xDirection = (_observationValues.x < 0) ? LOW : HIGH;
  int yDirection = (_observationValues.y < 0) ? LOW : HIGH;

  int xStepsCount = abs((int)(50. * _observationValues.x)) + 1;
  int yStepsCount = abs((int)(50. * _observationValues.x)) + 1;

  x.start(xDirection, xStepsCount);
  y.start(yDirection, yStepsCount);
}
