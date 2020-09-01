#include <Keyboard.h>
#include <Mouse.h>

const int ptt_button_pin = 2;
const int dip_mute_command_direct_pin = 8;
const int dip_mouse_keepalive_pin = 7;

bool ptt_button_current_state = false;
bool ptt_button_last_state = false;
bool dip_mute_command_direct = false;
bool dip_mouse_keepalive = false;

bool keyboard_active = false;
bool mouse_active = false;

//TODO: (Adam) 2002-09-01 Pretty sure you can check if Keyboard/Mouse is active without setting
//        tracking variables.
void activate_keyboard() {
    if (!keyboard_active) { 
      Mouse.end();
      mouse_active = false;
      Keyboard.begin();
      keyboard_active = true;
    }
}
void activate_mouse() {
  if (!mouse_active) {
    Keyboard.end();
    keyboard_active = false;
    Mouse.begin();
    mouse_active = true;
  }
}

void send_macos_mute_toggle() {
  //Send macOS Microsoft Teams "toggle mute" hotkey directly
  //WARNING: It will be picked up by whichever application is active!

  activate_keyboard();
  //Keyboard.print("direct");
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('m');
  delay(10);
  Keyboard.releaseAll();
}

void send_custom_hotkey() {
  //Send a custom hotkey to trigger Automator/Autohotkey action

  activate_keyboard();
  //Keyboard.print("custom_hotkey");
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F14);
  delay(10);
  Keyboard.releaseAll();
}

void read_dip_switches() {
  //NOTE: Switches are pulled to ground when active, don't forget to invert check!
  if (LOW == digitalRead(dip_mute_command_direct_pin)) { 
    dip_mute_command_direct = true; 
  } else {
    dip_mute_command_direct = false;
  }

  if (LOW == digitalRead(dip_mouse_keepalive_pin)) {
    dip_mouse_keepalive = true;
  } else {
    dip_mouse_keepalive = false;
  }
}
void read_buttons() {
  ptt_button_current_state = digitalRead(ptt_button_pin);

  read_dip_switches();
  if (ptt_button_last_state != ptt_button_current_state) {
    if (dip_mute_command_direct) {
      send_macos_mute_toggle(); 
    } else {
      send_custom_hotkey();
    }
  }
  ptt_button_last_state = ptt_button_current_state;
}

void start_mouse_keepalive() {
  //Move mnouse in a small pattern to keep a machine active.

  activate_mouse();
  for (;;) {
    read_dip_switches();
    if (!dip_mouse_keepalive) { break; }
    
    delay(random(500, 5000));
    Mouse.move(random(5, 25), 0, 0);
    delay(random(250, 500));
    Mouse.move(0, random(-25, -5), 0);
    delay(random(250, 500));
    Mouse.move(random(-25, -5), 0, 0);
    delay(random(250, 500));
    Mouse.move(0, random(5, 25), 0);
  }
}


void setup() {
  pinMode(ptt_button_pin, INPUT_PULLUP); 
  pinMode(dip_mute_command_direct_pin, INPUT_PULLUP);
  pinMode(dip_mouse_keepalive_pin, INPUT_PULLUP);
  
  ptt_button_last_state = digitalRead(ptt_button_pin);
}

void loop() {

  read_dip_switches();
  if (dip_mouse_keepalive) {
    start_mouse_keepalive();
  }
  
  read_buttons(); 

  delay(100);
}
