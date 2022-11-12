#include <TM1637Display.h> 

const uint8_t SEG_ON = 0xff;
const uint8_t SEG_OFF = 0x00;
const uint8_t SEG_ON_ALL[] = { SEG_ON, SEG_ON, SEG_ON, SEG_ON };
const uint8_t SEG_OFF_ALL[] = { SEG_OFF, SEG_OFF, SEG_OFF, SEG_OFF };

const uint8_t NUM_0 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
const uint8_t NUM_1 = SEG_E | SEG_F;
const uint8_t NUM_2 = SEG_A | SEG_B | SEG_D | SEG_E | SEG_G;
const uint8_t NUM_3 = SEG_A | SEG_B | SEG_C | SEG_D | SEG_G;
const uint8_t NUM_4 = SEG_B | SEG_C | SEG_F | SEG_G;
const uint8_t NUM_5 = SEG_A | SEG_C | SEG_D | SEG_F | SEG_G;
const uint8_t NUM_6 = SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
const uint8_t NUM_7 = SEG_A | SEG_B | SEG_C;
const uint8_t NUM_8 = SEG_ON;
const uint8_t NUM_9 = SEG_A | SEG_B | SEG_C | SEG_F | SEG_G;
const uint8_t NUM[] = { NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9 };

const uint8_t CHAR_C = SEG_A | SEG_D | SEG_E | SEG_F;
const uint8_t CHAR_E = SEG_A | SEG_D | SEG_E | SEG_F | SEG_G;
const uint8_t CHAR_F = SEG_A | SEG_E | SEG_F | SEG_G;
const uint8_t CHAR_R = SEG_E | SEG_G;

const uint8_t SYM_DEGREE = SEG_A | SEG_B | SEG_F | SEG_G;
const uint8_t SYM_DASH = SEG_G;

const uint8_t CHAR_ERR[] = { CHAR_E, CHAR_R, CHAR_R };

const uint8_t DISP_BRIGHT_0 = 0;
const uint8_t DISP_BRIGHT_1 = 1;
const uint8_t DISP_BRIGHT_2 = 2;
const uint8_t DISP_BRIGHT_3 = 3;
const uint8_t DISP_BRIGHT_4 = 4;
const uint8_t DISP_BRIGHT_5 = 5;
const uint8_t DISP_BRIGHT_6 = 6;
const uint8_t DISP_BRIGHT_7 = 7;
const uint8_t DISP_BRIGHT_MIN = DISP_BRIGHT_0;
const uint8_t DISP_BRIGHT_MAX = DISP_BRIGHT_7;

const uint8_t ANIM_LOOP_CW[][4] = {
  { SEG_A,    SEG_OFF,  SEG_OFF,  SEG_OFF },
  { SEG_OFF,  SEG_A,    SEG_OFF,  SEG_OFF },
  { SEG_OFF,  SEG_OFF,  SEG_A,    SEG_OFF },
  { SEG_OFF,  SEG_OFF,  SEG_OFF,  SEG_A },
  
  { SEG_OFF,  SEG_OFF,  SEG_OFF,  SEG_B },
  { SEG_OFF,  SEG_OFF,  SEG_OFF,  SEG_C },
  
  { SEG_OFF,  SEG_OFF,  SEG_OFF,  SEG_D },
  { SEG_OFF,  SEG_OFF,  SEG_D,    SEG_OFF },
  { SEG_OFF,  SEG_D,    SEG_OFF,  SEG_OFF },
  { SEG_D,    SEG_OFF,  SEG_OFF,  SEG_OFF },
  
  { SEG_E,    SEG_OFF,  SEG_OFF,  SEG_OFF },
  { SEG_F,    SEG_OFF,  SEG_OFF,  SEG_OFF },
};

void animateLoopClockwise(const TM1637Display *disp, const uint16_t timeMS);
