#include <Arduino.h>
#include <TM1637Display.h> 
#include "DisplayConstants.h"

void animate(const uint8_t frames[][4], const uint8_t frameCount, const TM1637Display *disp, const uint16_t timeMS, const uint8_t iterations) {
  const uint16_t interval = (timeMS / iterations) / frameCount;

  for (uint8_t i = 0; i < iterations; i++) {
    for (uint8_t f = 0; f < frameCount; f++) {
      disp->setSegments(frames[f]);
      delay(interval);
    }
  }
}

void animateLoopClockwise(const TM1637Display *disp, const uint16_t timeMS, const uint8_t iterations) {
  animate(ANIM_LOOP_CW, 12, disp, timeMS, iterations);
}
