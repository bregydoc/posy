#include "posy.h"
#include <Arduino.h>
// #include <EEPROM.h>
#include <WiFi.h>
#include "display.h"

// #define EEPROM_SIZE 10

#define ENC_A 0
#define ENC_B 4

unsigned long last_millis;
int number;
int current_menu;
int total_power;

bool hot_change = false;
bool power_change = false;

int encoder_position = 0;

unsigned long millis_debounce_encoder; 

const char* ssid = "Poseidon";
const char* password = "turingmachine";

WiFiServer server(80);

bool initialized = false;

Posy::Posy(int button_a, int button_b) {
  this->button_a = button_a;
  this->button_b = button_b;
}

int Posy::get_current_menu() {
  return current_menu;
}

void button_a_rising() {
  current_menu++;
  if (current_menu > 3) {
    current_menu = 0;
  }
  hot_change = true;
}

void process_operation() {
  if (current_menu == 0) {
    total_power = encoder_position;
    power_change = true;
  } // else if ...
}

void enc_change() {
  if (!initialized) {
    return;
  }

  if (digitalRead(ENC_A) && !digitalRead(ENC_B)) {
    encoder_position++;
    if (encoder_position > 99) {
      encoder_position = 99;
    }
  } else if (digitalRead(ENC_A) && digitalRead(ENC_B)) {
    encoder_position--;
    if (encoder_position < 0) {
      encoder_position = 0;
    }
  }

  millis_debounce_encoder = millis();
  
  Serial.println(encoder_position);
  process_operation();
}


void Posy::init() {
  // EEPROM.begin(EEPROM_SIZE);
  Serial.begin(9600);
  init_display();

  clear_display(0, 0, 7, 7);

  pinMode(this->button_a, INPUT);

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  attachInterrupt(digitalPinToInterrupt(this->button_a), button_a_rising, RISING);

  attachInterrupt(digitalPinToInterrupt(ENC_A), enc_change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), enc_change, CHANGE);

  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server started");

  // int last_saved_menu = EEPROM.read(0);

  // current_menu = last_saved_menu;
  // total_power = EEPROM.read(1);

  // uint32_t duty = uint32_t(map(total_power, 0, 99, 0, 1023));

  ledcSetup(0, 25000, 10);
  ledcAttachPin(PWM_FAN, 0);
  
  ledcWrite(0, 0);

  last_millis = millis();
  millis_debounce_encoder = millis();

  initialized = true;
}

void Posy::render() {
  draw_current_menu();
  if (current_menu == 0) {
    set_number(1, 3, total_power);
  } else if (current_menu == 1) {
    clear_display(1, 3, 7, 7);
  } else {
    clear_display(1, 3, 7, 7);
  }

  if (hot_change) {
    // EEPROM.write(0, current_menu);
    // EEPROM.commit();

    hot_change = false;
  }

  if (power_change) {
    uint32_t duty = uint32_t(map(total_power, 0, 99, 0, 1023));
    Serial.printf("duty: %d\n", duty);
    ledcWrite(0, duty);
    power_change = false;
  }

  fill_display(0, 0, 7, 7);
  
  render_state();
}

void Posy::draw_current_menu() {
  if (current_menu == 0) {
    draw_point(0, 0, HIGH);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  } else if (current_menu == 1) {
    draw_point(0, 0, LOW);
    draw_point(0, 1, LOW);
    draw_point(1, 0, HIGH);
    draw_point(1, 1, LOW);
  } else if (current_menu == 2) {
    draw_point(0, 0, LOW);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, HIGH);
  } else if (current_menu == 3) {
    draw_point(0, 0, LOW);
    draw_point(0, 1, HIGH);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  }
}

void Posy::draw_loading() {
  int step = this->loading_step % 4;
  if (step == 0) {
    draw_point(0, 0, HIGH);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  } else if (step == 1) {
    draw_point(0, 0, HIGH);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  } else if (step == 2) {
    draw_point(0, 0, HIGH);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  } else if (step == 3) {
    draw_point(0, 0, HIGH);
    draw_point(0, 1, LOW);
    draw_point(1, 0, LOW);
    draw_point(1, 1, LOW);
  }
  this->loading_step++;
}