#include <Arduino.h>
#include "UI.h"

UI ui;

void setup() {
  // put your setup code here, to run once:
  ui.begin();
  
  ui.Lcd.fillScreen(PINK);
}

void loop() {
  // put your main code here, to run repeatedly:
}