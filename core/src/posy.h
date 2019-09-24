#ifndef posy_h
#define posy_h

#define PWM_FAN 15

class Posy {
  
 private:
  int button_a = 12;
  int button_b = 13;
  int loading_step = 0;
  void draw_current_menu();
  void draw_loading();
  // void button_a_rising();
  // void button_b_rising();

 public:
  Posy(int button_a, int button_b);
  int get_current_menu();
  int set_current_menu(int menu);
  void init();
  void render();
};

#endif