#include <Keyboard.h>

const int ptt_button_pin = 2;

bool ptt_button_current_state = false;
bool ptt_button_last_state = false;

void setup() {
  pinMode(ptt_button_pin, INPUT_PULLUP); 
  ptt_button_last_state = digitalRead(ptt_button_pin);
  Keyboard.begin();
}

void loop() {
  ptt_button_current_state = digitalRead(ptt_button_pin);
  
  if (ptt_button_last_state != ptt_button_current_state) {
     //Keyboard.press(KEY_LEFT_GUI);
     //Keyboard.press(KEY_LEFT_SHIFT);
     //Keyboard.press('m');
     //delay(50);
     Keyboard.press(KEY_F20);
     Keyboard.releaseAll();
  }

  ptt_button_last_state = ptt_button_current_state;
  delay(100);
}
