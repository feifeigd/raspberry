#pragma once

#include <softPwm.h>	// softPwmCreate
#include <softTone.h>	// softToneWrite

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

	int SoftToneCreate(){
		return softToneCreate(pin_); // -1 失败
	}

	void SoftToneWrite(int freq){
		softToneWrite(pin_, freq); // 频率
	}
private:
	int pin_{};
};
