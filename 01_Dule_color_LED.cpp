
#include <Application.h>
#include <Gpio.h>

#include <iostream>

using namespace std;
typedef unsigned char uchar;

enum{
	makerobo_Led_PinRed = 0, // 红色LED灯引脚
	makerobo_Led_PinGreen = 1,// 绿色LED灯引脚
};

class Application: public base::Application{
public:
	bool init()override{
		int value = 0;
		int range = 100;
		red_.PwmCreate(value, range);
		green_.PwmCreate(value, range);
		return true;
	}

	// 设置led亮度，pwm调节范围是 0x00 ~ 0xff
	void SetColor(int red, int green){
		red_.PwmWrite(red);
		green_.PwmWrite(green);
	}

	void loop(){
		while(true){
			SetColor(0xff, 0x00); // 红色
			delay(500);

			SetColor(0x00, 0xff); // 绿色
			delay(500);
			
			SetColor(0xff, 0x45); // 
			delay(500);
			
			SetColor(0xff, 0xff); // 
			delay(500);
			
			SetColor(0x7c, 0xfc); // 
			delay(500);
		}

	}
private:
	Gpio red_{makerobo_Led_PinRed};
	Gpio green_{makerobo_Led_PinGreen};

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
