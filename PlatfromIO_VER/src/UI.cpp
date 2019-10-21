// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "UI.h"

#define BLK_PWM_CHANNEL 7 // LEDC_CHANNEL_7

UI::UI() : isInited(0) {
}

void UI::begin(bool LCDEnable, bool SDEnable, bool SerialEnable) {

  this->n.ReAllocate(18);

  // Correct init once
  if (isInited == true) {
    return;
  } else {
    isInited = true;
  }

  // UART
  if (SerialEnable == true) {
    Serial.begin(115200);
    Serial.flush();
    delay(50);
    Serial.print("M5Stack initializing...");
  }

  // LCD INIT
  if (LCDEnable == true) {
    Lcd.begin();
  }

  // TF Card
  if (SDEnable == true) {
    SD.begin(TFCARD_CS_PIN, SPI, 40000000);
  }

  if (SerialEnable == true) {
    Serial.println("OK");
  }

}


void UI::update(bool isConnected) {
  //Button update
  BtnA.read();
  BtnB.read();
  BtnC.read();
  //Display
  if (isConnected != last_status) {
	  Lcd.setCursor(16, 224);
	  Lcd.setTextSize(2);
	  Lcd.fillRect(16, 224, 160, 16, ILI9341_BLACK);
	  Lcd.setCursor(16, 224);
	  if (isConnected) {
		  Lcd.setTextColor(ILI9341_GREEN);
		  Lcd.print("Connected");
	  }
	  else {
		  Lcd.setTextColor(ILI9341_RED);
		  Lcd.print("Not Connected");
	  }
	  last_status = isConnected;
  }
  
  //Node
  for(int i = 0;i<this->index;i++){
    if( i % 6 < 3){
      if(i == icheck){
        if(n[i].data == 0)
          Lcd.setTextColor(PINK);
        else if(n[i].data == 1)
          Lcd.setTextColor(YELLOW);
      }
      else{
        if(n[i].data == 0)
          Lcd.setTextColor(WHITE);
        else if(n[i].data == 1)
          Lcd.setTextColor(YELLOW);
      }
      Lcd.setCursor(106*i+5,25);
      Lcd.print(n[i].label);
    }
    else{
      if(i == icheck){
        // if(n[i].data == 0)
        //   Lcd.setTextColor(PINK);
        // else if(n[i].data == 1)
        //   Lcd.setTextColor(YELLOW);
        // Lcd.setTextColor(PINK);        
      }
      else{
        if(n[i].data == 0)
          Lcd.setTextColor(WHITE);
        else if(n[i].data == 1)
          Lcd.setTextColor(YELLOW);
      }
      Lcd.setCursor(106*(i-3)+5,120);
      Lcd.print(n[i].label);
    }
    
  }

  if(BtnC.wasPressed()){
    
    if(n[icheck].data == 0 ){
      n[icheck].data = 1;
    }
    else if(n[icheck].data == 1){
      n[icheck].data = 0;
    }
  }
  else if(BtnA.wasPressed() && icheck > 0){
    this->icheck--;
  }
  else if(BtnB.wasPressed() && icheck < 5){
    this->icheck++;
  }
}

void UI::setBrightness(uint8_t brightness) {
  ledcWrite(BLK_PWM_CHANNEL, brightness);
}

int UI::getData(int index){
    return dataIn[index];
}

void UI::addNode(String Label,byte icon,byte mode){
    n.PushBack(Node(Label,this->index++,icon,mode));
    
}

void UI::writeData(int index,int data){
    
}
