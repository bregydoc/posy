#ifndef display_h
#define display_h

#include <Arduino.h>

void init_display(void);
void draw_point(uint8_t x, uint8_t y, bool level);
void set_digit(uint8_t x, uint8_t y, uint8_t number);
void set_number(uint8_t x, uint8_t y, uint8_t number);
void clear_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void fill_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void render_state();

#define NUM_0 {0b111, 0b101, 0b101, 0b101, 0b111}
#define NUM_1 {0b001, 0b001, 0b001, 0b001, 0b001}
#define NUM_2 {0b111, 0b001, 0b111, 0b100, 0b111}
#define NUM_3 {0b111, 0b001, 0b011, 0b001, 0b111}
#define NUM_4 {0b101, 0b101, 0b111, 0b001, 0b001}
#define NUM_5 {0b111, 0b100, 0b111, 0b001, 0b111}
#define NUM_6 {0b111, 0b100, 0b111, 0b101, 0b111}
#define NUM_7 {0b111, 0b001, 0b001, 0b001, 0b001}
#define NUM_8 {0b111, 0b101, 0b111, 0b101, 0b111}
#define NUM_9 {0b111, 0b101, 0b111, 0b001, 0b001}

#endif