#include "MicroBit.h"
MicroBit uBit;

uint8_t mail = 0;
uint8_t batt = 0;

const uint8_t blank_arr[] {
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, };

const uint8_t empty_mail_arr[] {
                          1, 0, 0, 0, 1,
                          0, 1, 0, 1, 0,
                          0, 0, 1, 0, 0,
                          0, 1, 0, 1, 0,
                          1, 0, 0, 0, 1, };


const uint8_t got_mail_arr[] {
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 1,
                          0, 0, 0, 1, 0,
                          1, 0, 1, 0, 0,
                          0, 1, 0, 0, 0, };

const uint8_t no_response_arr[] {
                          1, 1, 1, 1, 1,
                          1, 0, 0, 0, 1,
                          1, 0, 0, 0, 1,
                          1, 0, 0, 0, 1,
                          1, 1, 1, 1, 1, };


MicroBitImage blank(5,5,blank_arr);
MicroBitImage empty_mail(5,5,empty_mail_arr);
MicroBitImage got_mail(5,5,got_mail_arr);
MicroBitImage no_response(5,5,no_response_arr);



void onData(MicroBitEvent) {
    ManagedString s = uBit.radio.datagram.recv();

    if (s == "1") 
        mail = 1;
    
	if (s == "2") 
        mail = 2;

	if (s == "5") 
        batt = 1;
}

int main() {
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
	uBit.radio.enable();

	while(1) {

		if (uBit.buttonA.isPressed()) {

			//uBit.display.scroll(batt);
			if (batt == 0) {
				uBit.display.print(no_response);	// battery could be flat on the other side or no signal!
			}

			if (mail == 1 && batt == 1) {
				uBit.display.print(got_mail);	// we got mail!!
				uBit.radio.datagram.send("3");  // reset status (mail=2); 
				mail = 0; batt = 0;
			}
			
			if (mail == 2 && batt == 1) {
				uBit.display.print(empty_mail); // no mail
				mail = 0; batt = 0;
			}

			uBit.radio.datagram.send("4");

		}

		if (uBit.buttonB.isPressed()) 
			uBit.display.print(blank);
		

		uBit.sleep(500);
	}

}
