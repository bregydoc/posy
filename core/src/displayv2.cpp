#include "displayv2.h"

uint8_t nums[10][5] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9};

Display::Display(uint8_t orientation) {
  this->orientation = orientation;
}

void Display::init(void) {
  pinMode(SER, OUTPUT);
  pinMode(SRCLOCK, OUTPUT);
  pinMode(RCLOCK, OUTPUT);

  for (int i = 0; i < 8; i++) {
    this->display_state[i] = 0x00;
  }
}

void Display::draw_point(uint8_t x, uint8_t y, bool level) {
  if (level) {
    this->display_state[y] |= 1 << (7 - x);
  } else {
    this->display_state[y] &= ~(1 << (7 - x));
  }
}

void Display::draw_digit(uint8_t x, uint8_t y, uint8_t number) {
  uint8_t *num = nullptr;
  num = nums[number];

  for (int i = 0; i < 8; i++) {
    if (i >= y && !(i > y + 4)) {
      display_state[i] |= (((num[i - y])) << (5 - x));  // ((~(1 << (7 - x))) & display_state[i]);
    }
  }
}

void Display::draw_number(uint8_t x, uint8_t y, uint8_t number) {
  clear_display(x, y, x + 6, y + 5);
  uint8_t dec = number / 10;
  uint8_t un = number - (dec * 10);
  draw_digit(x, y, dec);
  draw_digit(x + 4, y, un);
}

void Display::clear_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  for (int i = y1; i < y2 + 1; i++) {
    this->display_state[i] &= ((255 << (8 - x1)) | ~(255 << (7 - x2)));
  }
}

void Display::fill_display(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  for (int i = y1; i < y2 + 1; i++) {
    this->display_state[i] |= ~((255 << (8 - x1)) | ~(255 << (7 - x2)));
  }
}

void Display::render_state() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(RCLOCK, LOW);
    if (this->orientation == 0) {
      shiftOut(SER, SRCLOCK, LSBFIRST, display_state[i]);
      shiftOut(SER, SRCLOCK, MSBFIRST, ~(1 << i));
    } else {
      shiftOut(SER, SRCLOCK, MSBFIRST, display_state[7 - i]);
      shiftOut(SER, SRCLOCK, LSBFIRST, ~(1 << (7 - i)));
    }
    digitalWrite(RCLOCK, HIGH);
    delayMicroseconds(1500);
  }
}
