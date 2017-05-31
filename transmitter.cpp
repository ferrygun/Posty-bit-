#include "MicroBit.h"
MicroBit uBit;

uint8_t mail = 0;

void onData(MicroBitEvent) {
    ManagedString s = uBit.radio.datagram.recv();
	//uBit.display.scroll(s);
    if (s == "3")  //Receive data from the other part to acknowledge and delete the flag.
        mail = 0;

	if (s == "4")
		uBit.radio.datagram.send("5");
}

int main() {
    uBit.init();
	int x = 0;

	//Setup a hander to run when data is received
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
	uBit.radio.enable();

    while(1) {
		x = uBit.io.P0.getAnalogValue(); // P0 is a value in the range of 0 - 1024 
		//uBit.display.scroll(x);
		
		if (x < 10)	
			mail = 1; //Mail is in the box

		if (mail == 1) //Mail is in the box 
			uBit.radio.datagram.send("1");
		
        if (mail == 0) //Mail is Not in the box
			uBit.radio.datagram.send("2");


        uBit.sleep(500);
    }
}
