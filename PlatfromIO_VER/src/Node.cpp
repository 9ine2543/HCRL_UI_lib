
#include "Node.h"

Node::Node(){
    
}
Node::Node(String label , byte index , byte icon, byte mode){
    this->label = label;
    this->index = index;
    this->icon = icon;
    this->mode = mode;
    this->data = 0;
	this->dout = 0;
	this->last = 0;

	this->labelColorSelected = 0xF81F;
	this->labelColorNotSelected = 0x7BEF;
	this->subLabelColor = 0xFFE0;
	this->iconColorOn = 0x07E0;
	this->iconColorOff = 0xF800;
	this->doutColor = 0xFFE0;
}


