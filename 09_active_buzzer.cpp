
#include <Application.h>
#include <Gpio.h>

#include <iostream>

using namespace std;
typedef unsigned char uchar;

enum{
	makerobo_Led_PinRed = 0, // 红色LED灯引脚
};

// 有源蜂鸣器
class Application: public base::Application{
public:
	bool init()override{
		red_.PinMode(OUTPUT);
		return true;
	}

	void loop(){
		while(true){
			red_.DigitalWrite(LOW);	// 低电平触发
			delay(500);
			red_.DigitalWrite(HIGH);	// 高电平关闭
			delay(500);
		}

	}
private:
	Gpio red_{makerobo_Led_PinRed};
};

int main(){
	Application app;
	if(app.setup() == -1){
		cout << "setup wiringPi failed!\n" << endl;
		return 1;
	}
	
	app.init();
	app.loop();

	return 0;
}
