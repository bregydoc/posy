#ifndef encoder_h
#define encoder_h

#include <Arduino.h>

class Encoder {
 private:
  uint8_t channel_a;
  uint8_t channel_b;
  int velocity;

  int value;

  int min;
  int max;

  int internal_counter = 0;
  bool initialized = false;

  void process_value();

 public:
  Encoder(int min, int max, uint8_t channel_a = 2, uint8_t channel_b = 3, int velocity = 300);
  void change_isr();
  void init();
  int get_value();
  void set_min(int value);
  void set_max(int value);
  uint8_t get_channel_a_interrupt();
  uint8_t get_channel_b_interrupt();
};
#endif