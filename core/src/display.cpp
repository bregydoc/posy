#include "display.h"
#include <Arduino.h>

#define SER 18
#define SRCLOCK 19
#define RCLOCK 21


uint8_t rows[8] = {22, 23, 5, 14, 27, 32, 33, 25};

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

uint8_t display_state[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

void init_display(void) {
  pinMode(SER, OUTPUT);
  pinMode(SRCLOCK, OUTPUT);
  pinMode(RCLOCK, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
  }
}

uint8_t reverse(uint8_t n) {
  uint8_t rev = 0;

  while (n > 0) {
    rev <<= 1;

    if ((n & 1) == 1)
      rev ^= 1;

    n >>= 1;
  }

  return rev;
}

void set_row(uint8_t row, bool level) {
  int i;
  for (i = 0; i < 8; i++) {
    if (i == row) {
      digitalWrite(rows[i], level);
    } else {
      digitalWrite(rows[i], ~level);
    }
  }
}

void render_state() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(RCLOCK, LOW);
    shiftOut(SER, SRCLOCK, LSBFIRST, display_state[i]);
    digitalWrite(RCLOCK, HIGH);
    set_row(i, LOW);
    delayMicroseconds(1500);
  }
}

void draw_point(uint8_t x, uint8_t y, bool level) {
  if (level) {
    display_state[y] |= 1 << (7 - x);
  } else {
    display_state[y] &= ~(1 << (7 - x));
  }
}

void set_digit(uint8_t x, uint8_t y, uint8_t number) {
  uint8_t *num = nullptr;
  if (number == 0) {
    num = num0;
  } else if (number == 1) {
    num = num1;
  } else if (number == 2) {
    num = num2;
  } else if (number == 3) {
    num = num3;
  } else if (number == 4) {
    num = num4;
  } else if (number == 5) {
    num = num5;
  } else if (number == 6) {
    num = num6;
  } else if (number == 7) {
    num = num7;
  } else if (number == 8) {
    num = num8;
  } else if (number == 9) {
    num = num9;
  } else {
    return;
  }

  for (int i = 0; i < 8; i++) {
    if (i >= y && !(i > y + 4)) {
      display_state[i] |= (((num[i - y])) << (5 - x));  // ((~(1 << (7 - x))) & display_state[i]);
    }
  }
}

void clear_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  for (int i = y1; i < y2 + 1; i++) {
    // display_state[i] = (1 << (7 - x1) & (~(1 << (7 - x2))));
    display_state[i] &= ((255 << (8 - x1)) | ~(255 << (7 - x2)));
  }
}

void fill_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  for (int i = y1; i < y2 + 1; i++) {
    display_state[i] |= ~((255 << (8 - x1)) | ~(255 << (7 - x2)));
  }
}

void set_number(uint8_t x, uint8_t y, uint8_t number) {
  clear_display(x, y, x + 6, y + 5);
  uint8_t dec = number / 10;
  uint8_t un = number - (dec * 10);
  set_digit(x, y, dec);
  set_digit(x + 4, y, un);
}