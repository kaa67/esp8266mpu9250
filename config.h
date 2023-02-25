#ifndef config_h
    #define config_h

    #define SKIP_VIBRATION_INTERVAL 30

    #define MPU6500_ADDR 0x68
    #define OBSERVATION_COUNT 10

    #define X_DIRECTION_PIN D5
    #define X_STEP_PIN D6
    #define Y_DIRECTION_PIN D7
    #define Y_STEP_PIN D8
    #define DRIVER_STEP_TIME_INTERVAL 1
#endif

#ifndef XYZ_FLOAT_H_
  #define XYZ_FLOAT_H_
  #include <xyzFloat.h>
  struct xyzFloat {
      float x;
      float y;
      float z;

      xyzFloat();
      xyzFloat(float const x, float const y, float const z);

      xyzFloat operator+() const;
      xyzFloat operator-() const;
      xyzFloat operator+(xyzFloat const & summand) const;
      xyzFloat operator-(xyzFloat const & subtrahend) const;
      xyzFloat operator*(float const operand) const;
      xyzFloat operator/(float const divisor) const;
      xyzFloat & operator+=(xyzFloat const & summand);
      xyzFloat & operator-=(xyzFloat const & subtrahend);
      xyzFloat & operator*=(float const operand);
      xyzFloat & operator/=(float const divisor);
  };
#endif
