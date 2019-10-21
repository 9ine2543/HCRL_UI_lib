#include <Arduino.h>
#include <UI.h>

UI Ui;
void setup(void)
{
	Ui.begin();
	Ui.setBrightness(100);
	for(int i = 0 ;i<5;i++){
		Ui.addNode("NINE",0,0);
	}
		
}
bool con;
long last;

void loop(void)
{
	if (millis() - last > 3000) {
		con = !con;
		last = millis();
	}
	
	Ui.update(con);
}