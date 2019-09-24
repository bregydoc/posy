#include <Arduino.h>
#include "displayv2.h"
#include "encoder.h"

#define ENC_CH_A 3
#define ENC_CH_B 2

#define DISPL_SER 4
#define DISPL_CLOCK 5
#define DISPL_LATCH 6

unsigned long ms;

Display display = Display(DISPL_SER, DISPL_CLOCK, DISPL_LATCH, 1);

Encoder encoder = Encoder(0, 99, ENC_CH_A, ENC_CH_B, 220);

int level = 0;

void local_isr() {
  encoder.change_isr();
}

void setup() {
  Serial.begin(9600);
  display.init();
  encoder.init();

  attachInterrupt(encoder.get_channel_a_interrupt(), local_isr, RISING);
  attachInterrupt(encoder.get_channel_b_interrupt(), local_isr, FALLING);

  ms = millis();
  display.fill_display(0, 0, 7, 7);
}

void loop() {
  if (millis() - ms > 100) {
    display.clear_display(0, 0, 7, 7);
    display.fill_display(4 - level, 4 - level, level + 3, level + 3);
    level++;
    if (level > 4)
      level = 1;

    ms = millis();
  }
  display.render_state();
}
