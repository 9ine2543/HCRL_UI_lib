
#include "Node.h"

Node::Node(){
    
}
Node::Node(String label , byte index , byte icon, byte mode){
    this->label = label;
    this->index = index;
    this->icon = icon;
    this->mode = mode;
    this->data = 0;
}
String Node::getLabel(){
    return this->label;
}


