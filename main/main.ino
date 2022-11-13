#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <TM1637Display.h>
#include "DisplayConstants.h"

const uint8_t RELAY_PIN = 2;
const uint8_t DISP_DIO_PIN = 4;
const uint8_t DISP_PIN_CLK = 5;
const uint8_t TEMP_PIN = 10;

const uint16_t DISP_INTERVAL_MS = 2000;
const uint16_t FADE_IN_MS = 1000;
const uint16_t FADE_OUT_MS = 500;
const uint16_t ANIM_DELAY_MS = 2000;
const int8_t TEMP_ON_C = -20;
const int8_t TEMP_OFF_C = -15;
const TM1637Display disp = TM1637Display(DISP_PIN_CLK, DISP_DIO_PIN);
const DHT_Unified sensor(TEMP_PIN, DHT22);

uint16_t tempDelayMS = 30000;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  initSensor();
  initDisplay();
}

void initSensor() {
  const sensor_t sensorInfo;

  sensor.begin();
  sensor.temperature().getSensor(&sensorInfo);
  tempDelayMS = max(tempDelayMS, sensorInfo.min_delay / 1000);
}

void initDisplay() {
  uint8_t segments[4];
  
  for (uint8_t i = 0; i < 4; i++) {
    segments[i] = SYM_DASH;
  }
  
  disp.setBrightness(DISP_BRIGHT_MIN);
  fadeIn(segments, 1000);
}

void loop() {
  const int8_t tempC = readTemp();
  
  if (tempC != NULL) {
    toggleRelay(tempC);
    displayTempC(tempC);
    displayTempF(tempC);
  }

  disp.setBrightness(DISP_BRIGHT_MIN);

  for (uint8_t i = 0; i < tempDelayMS / ANIM_DELAY_MS; i++) {
    animateLoopClockwise(&disp, ANIM_DELAY_MS);
  }
}

int8_t readTemp() {
    const sensors_event_t event;
  
    sensor.temperature().getEvent(&event);
    
    if (isnan(event.temperature)) {
      displayError(2, "Failed to read temperature.");
      
      return NULL;
    }
    else {
      return event.temperature;
    }
}

void toggleRelay(const int8_t tempC) {
  if (tempC > TEMP_ON_C) {
    digitalWrite(RELAY_PIN, HIGH);
  }
  else if (tempC <= TEMP_OFF_C) {
    digitalWrite(RELAY_PIN, LOW);
  }
}

void displayTempC(const int8_t tempC) {
  displayTemp(tempC, CHAR_C);
}

void displayTempF(const int8_t tempC) {
  const int8_t tempF = (tempC * 1.8) + 32;
  
  displayTemp(tempF, CHAR_F);
}

void displayTemp(const int8_t temp, const uint8_t unit) {
    const int8_t constraintedTemp = constrain(temp, -99, 99);
    const bool isNegative = constraintedTemp < 0;
    const bool showDegree = constraintedTemp > -9;
    const bool showFirstDigit = constraintedTemp < -9 || constraintedTemp > 9;
    const int8_t firstDigit = getDigit(constraintedTemp, 1);
    const int8_t secondDigit = getDigit(constraintedTemp, 0);
    const uint8_t firstNum = NUM[firstDigit];
    const uint8_t secondNum = NUM[secondDigit];
    uint8_t segments[4];

    if (isNegative) {
      segments[0] = SYM_DASH;

      if (showDegree) {
        segments[1] = secondNum;
        segments[2] = SYM_DEGREE;
      }
      else {
        segments[1] = showFirstDigit? firstNum : SEG_OFF;
        segments[2] = secondNum;
      }
    }
    else {
      segments[0] = showFirstDigit ? firstNum : SEG_OFF;
      segments[1] = secondNum;
      segments[2] = SYM_DEGREE;
    }

    segments[3] = unit;
  
    fadeIn(segments, FADE_IN_MS);
    delay(DISP_INTERVAL_MS);
    fadeOut(segments, FADE_OUT_MS);
}

void fadeIn(const uint8_t segments[], const uint16_t timeMS) {
  disp.clear();
  fade(segments, timeMS, true);
}

void fadeOut(const uint8_t segments[], const uint16_t timeMS) {
  fade(segments, timeMS, false);
  disp.clear();
}

void fade(const uint8_t segments[], const uint16_t timeMS, const bool in) {
  const uint8_t levels = DISP_BRIGHT_MAX + 1;
  const uint8_t interval = timeMS / levels;
  const uint8_t fadeStart = in ? DISP_BRIGHT_MIN : DISP_BRIGHT_MAX;
  const uint8_t fadeEnd = in ? DISP_BRIGHT_MAX : DISP_BRIGHT_MIN;
  const uint8_t step = in ? 1 : -1;

  for (uint8_t i = fadeStart; i != fadeEnd + step; i += step) {
    disp.setBrightness(i);
    disp.setSegments(segments, 4, 0);

    if (i != fadeEnd) {
      delay(interval);
    }
  }
}

int16_t getDigit(const int16_t number, const uint8_t position) {
  const uint8_t digit = (abs(number) / ((int) pow(10, position)) % 10);

  return digit;
}

void displayError(const uint8_t code, char* message) {
  Serial.print("ERROR! ");
  Serial.println(message);
    
  disp.setSegments(CHAR_ERR, 3, 0);
  setSegment(code, 3);
}

void setSegment(const uint8_t value, const uint8_t position) {
  disp.showNumberDec(value, false, 1, position);
}
