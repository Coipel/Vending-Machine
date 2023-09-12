#include "utility.h"

Input priority_input(int* input_pins, int input_pins_size) {
  for (int i = 0; i != input_pins_size; i++) {
    if (digitalRead(input_pins[i]) == 0)
      return Input(i);
  }
  return Input::none;
}

void rotate_motor(int motor_pin, int powered_time_ms) {
  digitalWrite(motor_pin, LOW);
  delay(powered_time_ms);
  digitalWrite(motor_pin, HIGH);
}



