#include "encoder.h"

#define MULTIPLIER 16

void Encoder::change_isr() {
  if (digitalRead(this->channel_a) && !digitalRead(this->channel_b)) {
    this->internal_counter++;
    this->process_value();
    return;
  }

  if (!digitalRead(this->channel_a) && digitalRead(this->channel_b)) {
    this->internal_counter--;
    this->process_value();
    return;
  }
}

void Encoder::process_value() {
  this->value = map(this->internal_counter / MULTIPLIER, 0, this->velocity, this->min, this->max + 1);

  if (this->internal_counter < 0) {
    this->internal_counter = this->velocity * MULTIPLIER;
    return;
  }

  if (this->internal_counter > this->velocity * MULTIPLIER) {
    this->internal_counter = 0;
    return;
  }
}

Encoder::Encoder(int min, int max, uint8_t channel_a = 2, uint8_t channel_b = 3, int velocity = 300) {
  this->min = min;
  this->max = max;
  this->channel_a = channel_a;
  this->channel_b = channel_b;
  this->velocity = velocity;

  this->value = 0;
}

void Encoder::init() {
  pinMode(this->channel_a, INPUT_PULLUP);
  pinMode(this->channel_b, INPUT_PULLUP);

  this->initialized = true;
}

int Encoder::get_value() {
  if (!this->initialized) {
    return 0;
  }
  return this->value;
}

void Encoder::set_min(int value) {
  if (!this->initialized) {
    return;
  }

  this->min = value;
}

void Encoder::set_max(int value) {
  if (!this->initialized) {
    return;
  }

  this->max = value;
}

uint8_t Encoder::get_channel_a_interrupt() {
  return digitalPinToInterrupt(this->channel_a);
}

uint8_t Encoder::get_channel_b_interrupt() {
  return digitalPinToInterrupt(this->channel_b);
}
