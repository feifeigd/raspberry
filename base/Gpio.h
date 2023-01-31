#pragma once

#include <softPwm.h>	// softPwmCreate
#include <wiringPi.h>	// pinMode

class Gpio{
public:
	Gpio(int pin): pin_{pin}{}

	int PwmCreate(int value, int range){
		return softPwmCreate(pin_, value, range);
	}
	void PwmWrite(int value){
		return softPwmWrite(pin_, value);
	}

	void PinMode(int mode){
		pinMode(pin_, mode);
	}

	int DigitalRead(){
		return digitalRead(pin_);
	}
	
	void DigitalWrite(int value){
		digitalWrite(pin_, value);
	}

private:
	int pin_{};
};
