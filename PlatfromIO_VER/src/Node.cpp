
#include "Node.h"

Node::Node(){

}

void Node::add(String label , byte index , byte icon, byte mode){
    this->label = label;
    this->index = index;
    this->icon = icon;
    this->mode = mode;
    this->data = 0;

    if(this->index == 1){
        Lcd.setCursor(25, 25);
        Lcd.setTextColor(WHITE);
        Lcd.setTextSize(3);
        Lcd.printf("%s",this->label);
    }
}

void Node::update() {
    BtnB.read();
    if(BtnB.wasPressed() == 1){
        if(this->index == 1){
            if(this->data == 0){
                Lcd.setCursor(25, 25);
                Lcd.setTextColor(PINK);
                Lcd.printf("%s",this->label);
                data = 1;
            }
            else if(this->data == 1){
                Lcd.setCursor(25, 25);
                Lcd.setTextColor(WHITE);
                Lcd.printf("%s",this->label);
                data = 0;
            }
        }
        
    }
}


