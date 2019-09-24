#include <Arduino.h>
#include "displayv2.h"
#include "posy.h"

#define PELTIER 2

// Posy posy = Posy(12, 13);
ulong ms;
int counter_x = 0;
int counter_y = 0;

bool to_draw = true;

Display display = Display(1);

void setup() {
  Serial.begin(9600);
  display.init();
  pinMode(PELTIER, OUTPUT);
  digitalWrite(PELTIER, HIGH);
  display.fill_display(0, 0, 6, 6);
  display.clear_display(0, 0, 7, 7);
  ms = millis();
}

void loop() {
  if (millis() - ms >= 200) {
    display.draw_number(1, 2, counter_x);
    counter_x++;
    if (counter_x > 99) {
      counter_x = 0;
    }
    // if (counter_x > 7) {
    //   counter_x = 0;
    // }
    // if (counter_y > 7) {
    //   counter_y = 0;
    //   to_draw = !to_draw;
    // }
    Serial.printf("(%d)\n", counter_x);
    ms = millis();
  }
  display.render_state();
}
