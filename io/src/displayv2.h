#ifndef display_h
#define display_h

#include <Arduino.h>

#define NUM_0 { 0b111, 0b101, 0b101, 0b101, 0b111 }
#define NUM_1 { 0b001, 0b001, 0b001, 0b001, 0b001 }
#define NUM_2 { 0b111, 0b001, 0b111, 0b100, 0b111 }
#define NUM_3 { 0b111, 0b001, 0b011, 0b001, 0b111 }
#define NUM_4 { 0b101, 0b101, 0b111, 0b001, 0b001 }
#define NUM_5 { 0b111, 0b100, 0b111, 0b001, 0b111 }
#define NUM_6 { 0b111, 0b100, 0b111, 0b101, 0b111 }
#define NUM_7 { 0b111, 0b001, 0b001, 0b001, 0b001 }
#define NUM_8 { 0b111, 0b101, 0b111, 0b101, 0b111 }
#define NUM_9 { 0b111, 0b101, 0b111, 0b001, 0b001 }

class Display {
 private:
  uint8_t display_state[8];
  uint8_t orientation = 0;
  
  uint8_t ser = 2;
  uint8_t clock = 3;
  uint8_t latch = 4;

  uint8_t num0[5] = NUM_0;
  uint8_t num1[5] = NUM_1;
  uint8_t num2[5] = NUM_2;
  uint8_t num3[5] = NUM_3;
  uint8_t num4[5] = NUM_4;
  uint8_t num5[5] = NUM_5;
  uint8_t num6[5] = NUM_6;
  uint8_t num7[5] = NUM_7;
  uint8_t num8[5] = NUM_8;
  uint8_t num9[5] = NUM_9;

  bool initialized = false;

 public:
  Display(uint8_t ser, uint8_t clock, uint8_t latch, uint8_t orientation = 0);
  void init(void);
  void draw_point(uint8_t x, uint8_t y, bool level);
  void draw_digit(uint8_t x, uint8_t y, uint8_t number);
  void draw_number(uint8_t x, uint8_t y, uint8_t number);
  void clear_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void fill_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void render_state();
};

#endif