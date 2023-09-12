/*
  Project Information: The following program is intended as a recreation of what was accomplisihed through hardware by Anthony Coipel in a software form.
  Most hardware limitations/difficultlies will be carried over in software (example: lowest denomination of currency being quarters)
*/

#include "utility.h"

const int motor_item1_pin = 13, 
          motor_item2_pin = 12, 
          motor_item3_pin = 14, 
          motor_item4_pin = 27, 
          motor_refund_pin = 25;
        
const int item1_pin = 4, 
          item2_pin = 5, 
          item3_pin = 18, 
          item4_pin = 19, 
          refund_pin = 21, 
          quarter_pin = 22, 
          one_dollar_pin = 23,
          five_dollar_pin = 15;

// For convenience the following arrays are defined
int output_pins[5] = {motor_item1_pin, 
                      motor_item2_pin, 
                      motor_item3_pin, 
                      motor_item4_pin, 
                      motor_refund_pin};

const int output_pins_size = sizeof(output_pins)/sizeof(int);

int input_pins[8] = {item1_pin, 
                     item2_pin, 
                     item3_pin, 
                     item4_pin, 
                     refund_pin, 
                     quarter_pin, 
                     one_dollar_pin,
                     five_dollar_pin};

const int input_pins_size = sizeof(input_pins)/sizeof(int);

// How much money the user has put in the machine in amount of quarters
int quarters = 0;

void setup() {
  Serial.begin(9600);
  
  // Output pins that are the source of the signal that would drive a motor that would cause an item to be dispensed or a quarter being refunded
  for (int i = 0; i != output_pins_size; i++) {
    pinMode(output_pins[i], OUTPUT);
    digitalWrite(output_pins[i], HIGH);
  }

  // Input pins that are the user input to select what item they request to be dispensed or what special operation to perform (ex: refund)
  for (int i = 0; i != input_pins_size; i++)
    pinMode(input_pins[i], INPUT_PULLUP);
}

void loop() {
  Input input = priority_input(input_pins, input_pins_size);
  while (input == Input::none) 
    input = priority_input(input_pins, input_pins_size);
  while (priority_input(input_pins, input_pins_size) != Input::none) // Prevent the button from being held down
    delay(500); 

  switch (input) {
    case Input::quarter:
      Serial.println("Quarter Added");
      quarters += 1;
      break;

    case Input::one_dollar:
      Serial.println("Dollar Added");
      quarters += 4;
      break;
    
    case Input::five_dollar:
      Serial.println("Five Dollars Added");
      quarters += 20;
      break;
    
    case Input::refund:
      Serial.println("Refund Selected");
      while (quarters > 0) {
        Serial.println("Returned Coin");
        quarters -= 1;
        rotate_motor(motor_refund_pin, 500);
        delay(500); // Delay is for a hypotetical spring to reset coin ejector
        
        if (quarters != 0) {
          Serial.print("Quarters: ");
          Serial.println(quarters);
        }
      }
      break;

    case Input::item1:
      Serial.println("Item 1 Selected ($3.75)");
      if (quarters >= 15) {
        quarters -= 15;
        Serial.println("Dispensing Item 1...");
        rotate_motor(motor_item1_pin, 5000);
        Serial.println("Dispensed Item 1");
      }
      else
        Serial.println("Not Enough Funds");
      break;

    case Input::item2:
      Serial.println("Item 2 Selected ($5)");
      if (quarters >= 20) {
        quarters -= 20;
        Serial.println("Dispensing Item 2...");
        rotate_motor(motor_item2_pin, 5000);
        Serial.println("Dispensed Item 2");
      }
      else
        Serial.println("Not Enough Funds");
      break;

    case Input::item3:
      Serial.println("Item 3 Selected ($1)");
      if (quarters >= 4) {
        quarters -= 4;
        Serial.println("Dispensing Item 3...");
        rotate_motor(motor_item3_pin, 5000);
        Serial.println("Dispensed Item 3");
      }
      else
        Serial.println("Not Enough Funds");
      break;

    case Input::item4:
      Serial.println("Item 4 Selected ($0.50)");
      if (quarters >= 2) {
        quarters -= 2;
        Serial.println("Dispensing Item 4...");
        rotate_motor(motor_item4_pin, 5000);
        Serial.println("Dispensed Item 4");
      }
      else
        Serial.println("Not Enough Funds");
      break;
  }

  Serial.print("Quarters: ");
  Serial.println(quarters);
}
