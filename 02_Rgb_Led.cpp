
#include <Application.h>
#include <Gpio.h>

#include <iostream>

using namespace std;
typedef unsigned char uchar;

enum{
	eLed_PinRed = 0, // 红色LED灯引脚
	eLed_PinGreen = 1,// 绿色LED灯引脚
	eLed_PinBlue = 2,// 蓝色LED灯引脚
};

class Application: public base::Application{
public:
	bool init()override{
		int value = 0;
		int range = 100;
		red_.PwmCreate(value, range);
		green_.PwmCreate(value, range);
		blue_.PwmCreate(value, range);
		return true;
	}

	// 设置led亮度，pwm调节范围是 0x00 ~ 0xff
	void SetColor(int red, int green, int blue){
		red_.PwmWrite(red);
		green_.PwmWrite(green);
		blue_.PwmWrite(blue);
	}

	void loop(){
		while(true){
			SetColor(0xff, 0x00, 0x00); // 红色
			delay(500);

			SetColor(0x00, 0xff, 0x00); // 绿色
			delay(500);
			
			SetColor(0x00, 0x00, 0xff); // 蓝色
			delay(500);

			SetColor(0xff, 0xff, 0x00); // 黄色
			delay(500);
			
			SetColor(0xff, 0x00, 0xff); // pick
			delay(500);
			
			SetColor(0xc0, 0xff, 0x3e); // 
			delay(500);
			
			SetColor(0x94, 0x00, 0xd3); // 
			delay(500);
			
			SetColor(0x76, 0xee, 0x00); // 
			delay(500);
			
			SetColor(0x00, 0xc5, 0xcd); // 
			delay(500);
		}

	}
private:
	Gpio red_{eLed_PinRed};
	Gpio green_{eLed_PinGreen};
	Gpio blue_{eLed_PinBlue};

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
