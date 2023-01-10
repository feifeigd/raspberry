#pragma once

#include <softPwm.h>	// softPwmCreate

class Gpio{
public:
	Gpio(int pin): pin_{pin}{}

	int PwmCreate(int value, int range){
		return softPwmCreate(pin_, value, range);
	}
	void PwmWrite(int value){
		return softPwmWrite(pin_, value);
	}
private:
	int pin_{};
};
