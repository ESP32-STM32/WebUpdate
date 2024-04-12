#include "WIFI.h"

#define LED 2

unsigned long tmrLED;       //
boolean flagLEDoff = true;  // Светодиод
boolean flagLEDon;          //

void setup(void) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  initWIFI();
}

void loop(void) {
  handleUP();
  led();
}

void led() {
  if (millis() - tmrLED >= 100) {
    tmrLED = millis();
    if (flagLEDoff) {
      digitalWrite(LED, LOW);
      flagLEDoff = false;
      flagLEDon = false;
    } else if (flagLEDon) {
      digitalWrite(LED, HIGH);
      flagLEDoff = true;
    }
    flagLEDon = true;
  }
}
