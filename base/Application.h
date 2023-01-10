#pragma once

// 安装wiringPI库 https://github.com/guation/WiringPi-arm64 

#include <wiringPi.h>	// wiringPiSetup

namespace base{
	class Application{
	public:
		int setup();
		virtual bool init() = 0;
	};
}
