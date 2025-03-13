#include "Arduino.h"

const int leds[3] = {D1, D2, D3};
const int buttons[3] = {D5, D6, D7};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }

  if (digitalRead(buttons[0]) == LOW) {
    while (digitalRead(buttons[0]) == LOW)
      ;

    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], HIGH);
      delay(500);
    }

  } else if (digitalRead(buttons[1]) == LOW) {
    while (digitalRead(buttons[1]) == LOW)
      ;

    for (int i = 0; i < 3; i++) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(leds[i], HIGH);
        delay(500);
        digitalWrite(leds[i], LOW);
      }
    }

  } else if (digitalRead(buttons[2]) == LOW) {
    while (digitalRead(buttons[2]) == LOW)
      ;

    for (int count = 0; count < 8; count++) {
      digitalWrite(leds[0], (count & 1) ? HIGH : LOW);
      digitalWrite(leds[1], (count & 2) ? HIGH : LOW);
      digitalWrite(leds[2], (count & 4) ? HIGH : LOW);

      delay(500);
    }
  }
}
