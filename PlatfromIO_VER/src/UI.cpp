// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "UI.h"

#define BLK_PWM_CHANNEL 7 // LEDC_CHANNEL_7

UI::UI() : isInited(0) {
}

void UI::begin(uint16_t bgColor, bool LCDEnable, bool SDEnable, bool SerialEnable) {

  this->n.ReAllocate(19);

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
    Lcd.begin(bgColor);
	this->backgroundColor = bgColor;
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
	  Lcd.fillRect(16, 224, 160, 16, backgroundColor);
	  last_status = isConnected;
  }
  Lcd.setTextSize(2);
  Lcd.setCursor(16, 224);
  if (isConnected) {
	  Lcd.setTextColor(GREEN);
	  Lcd.print("Connected");
  }
  else {
	  Lcd.setTextColor(RED);
	  Lcd.print("Not Connected");
  }
  
  if(BtnC.wasPressed()){
    
    if(n[icheck].data == 0 ){
      n[icheck].data = 1;
    }
    else if(n[icheck].data == 1){
      n[icheck].data = 0;
    }
  }
  else if(BtnA.wasPressed()){
	  do{
			if (this->icheck - 1 < 0) {
				this->icheck = this->index-1;
			}
			else {
				this->icheck--;
			}
	  } while (n[this->icheck].mode == OUPT);
  }
  else if(BtnB.wasPressed()){
	  do{
			if (this->icheck + 1 > this->index-1) {
				this->icheck = 0;
			}
			else {
				this->icheck++;
			}
	  } while (n[this->icheck].mode == OUPT);
  }

  //Node
  //Compute the Pages
  int currentPage = icheck / 6; // 0 1 2
  int start = currentPage * 6; // 0 6 12
  int totalPage;
  if (index > 12) totalPage = 3;
  else if (index > 6) totalPage = 2;
  else totalPage = 1;
  int end;
  if (currentPage + 1 == totalPage) {
	  if (index != 0 and index % 6 == 0) {
		  end = start + 6;
	  }
	  else end = index % 6 + start;
  }
  else end = start + 6;

  if (last_page != currentPage) {
	  Lcd.fillScreen(backgroundColor);
	  last_page = currentPage;
  }

  //Update Pages
  for (int i = start; i < end; i++) {
	  int x0 = (i % 3) * BOX_WIDTH + (i % 3) + 5;
	  int y0 = (i / 3)%2 * BOX_HEIGHT + (i / 3)%2 + 3;
	  Lcd.setTextSize(2);
	  Lcd.setCursor(x0, y0);
	  if (n[i].mode == OUPT) {
		  //read and print data from node
		    Lcd.setTextColor(n[i].labelColorNotSelected);
			Lcd.print(n[i].label);
			Lcd.setCursor(x0, y0 + SIZE2PX + 5);
			Lcd.setTextColor(n[i].subLabelColor);
			Lcd.print(n[i].subLabel);
			if (n[i].dout != n[i].last) {
				//Do something with Icon here
				Lcd.setCursor(x0, y0 + SIZE2PX * 3 + 10);
				Lcd.setTextColor(backgroundColor);
				Lcd.printf(" %.2f", n[i].last);
				Lcd.setCursor(x0, y0 + SIZE2PX * 3 + 10);
				Lcd.setTextColor(n[i].doutColor);
				Lcd.setTextSize(2);
				Lcd.printf(" %.2f", n[i].dout);
				n[i].last = n[i].dout;
			}
	  }
	  else {
		  //check input and write data to node
		  if (i == icheck) {
				Lcd.setTextColor(n[i].labelColorSelected);
		  }
		  else {
				Lcd.setTextColor(n[i].labelColorNotSelected);
		  }
		  Lcd.print(n[i].label);
		  //Do something with Icon here
		  if (n[i].data != (int)(n[i].last)) {
			  Lcd.setCursor(x0, y0 + SIZE2PX + 5);
			  Lcd.setTextColor(backgroundColor);
			  Lcd.print((int)(n[i].last));
			  n[i].last = n[i].data;
		  }
		  Lcd.setCursor(x0, y0 + SIZE2PX + 5);
		  if (n[i].data == 0)
			  Lcd.setTextColor(n[i].iconColorOff);
		  else if (n[i].data == 1)
			  Lcd.setTextColor(n[i].iconColorOn);
		  Lcd.print(n[i].data);
	  }
  }

  //Refresh Grid
  Lcd.drawGridUi(icheck);
}

void UI::addNode(String Label, byte icon, byte mode) {
	Label = Label.substring(0, 8);
	n.PushBack(Node(Label, this->index++, icon, mode));
}

void UI::setBrightness(uint8_t brightness) {
  ledcWrite(BLK_PWM_CHANNEL, brightness);
}

int UI::getData(int index){
    return n[index].data;
}

float UI::getDout(int index) {
	return n[index].dout;
}

String UI::getLabel(int index) {
	return n[index].label;
}

String UI::getSubLabel(int index) {
	return n[index].subLabel;
}

void UI::write(int index,float data){
	if (n[index].mode == OUPT) {
		n[index].dout = data;
	}
	else {
		n[index].data = (int)data;
	}

}

void UI::setLabel(int index, String label) {
	label = label.substring(0, 8);
	n[index].label = label;
}

void UI::setSubLabel(int index, String sub) {
	sub = sub.substring(0, 8);
	n[index].subLabel = sub;
}

void UI::setLabelColor(int index, uint16_t selected, uint16_t notSelected) {
	n[index].labelColorSelected = selected;
	n[index].labelColorNotSelected = notSelected;
}

void UI::setLabelColor(int index, uint16_t notSelected) {
	n[index].labelColorNotSelected = notSelected;
}

void UI::setSubLabelColor(int index, uint16_t color) {
	n[index].subLabelColor = color;
}

void UI::setIconColor(int index, uint16_t on, uint16_t off) {
	n[index].iconColorOn = on;
	n[index].iconColorOff = off;
}

void UI::setIconColor(int index, uint16_t color) {
	n[index].iconColorOn = color;
	n[index].iconColorOff = color;
}

void UI::setDoutColor(int index, uint16_t color) {
	n[index].doutColor = color;
}