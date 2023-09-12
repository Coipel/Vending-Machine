#include <Arduino.h>

/*
  After deciphering my old notes it seems that aux1 (T1) = refund, aux2 (T2) = quarter, aux3 (T3) = dollar input (except it can vary between $1 & $5 
  based on external none button input) (T1-T2-T3 are going left to right after item buttons) I will add an aux4 to have aux3 be for $1 and aux4
  for $5. Note it was expected that a hidden input of a scanner would determine what to do after pushing the original dollar button and it would 
  have decided if it were $1, $5, or invalid and respond accordingly. With the above change there is no longer an invalid state or hidden input.
  In addition there was hardware intended to return the "bill" whenever the "scanner" detected it as invalid through motor direction changes. This
  currency varification section will be skipped in software and could be considered its own seperate project whereas this one is the actions to take
  after currency has been verified as either a quarter, one dollar, or five dollar.
*/

enum Input {none = -1, item1, item2, item3, item4, refund, quarter, one_dollar, five_dollar};

// From all the inputs returns the index of the very first button push encountered (serves as a priority encoder)
Input priority_input(int* input_pins, int input_pins_size);

// Rotating motors is how things such as items are dispensed or refunds provided
void rotate_motor(int motor_number, int powered_time_ms = 5000);

