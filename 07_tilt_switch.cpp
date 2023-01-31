
#include <Application.h>
#include <Gpio.h>

#include <iostream>

using namespace std;
typedef unsigned char uchar;

enum{
	makerobo_BtnPin = 0,	// 按钮pin引脚
	makerobo_Led_PinRed = 1, // 红色LED灯引脚
	makerobo_Led_PinGreen = 2,// 绿色LED灯引脚
};

class Application: public base::Application{
public:
	bool init()override{
		// 输入模式
		btn_.PinMode(INPUT);

		// 设置为输出模式
		red_.PinMode(OUTPUT);
		green_.PinMode(OUTPUT);

		SetColor("makeroboGREEN");

		return true;
	}

	// 
	void SetColor(char const* color){
		// 设置为输出模式
		red_.PinMode(OUTPUT);
		green_.PinMode(OUTPUT);
		if("makeroboRED" == color){	// 点亮红色
			red_.DigitalWrite(HIGH);
			green_.DigitalWrite(LOW);
			cout << "red" << endl;
		}else if("makeroboGREEN" == color){  // 点亮绿色
			red_.DigitalWrite(LOW);
			green_.DigitalWrite(HIGH);
			cout << "green" << endl;
		}else cerr << "makerobo Double color LED Error!" << endl;
	}

	void loop(){
		while(true){
			if(0 == btn_.DigitalRead()){ // 按钮按下
				delay(10); // 延时去抖动
				if(0 == btn_.DigitalRead()){
					SetColor("makeroboRED");
					cout << "Button is pressed!" << endl;
				}else if(1 == btn_.DigitalRead()){ 
					delay(10); // 延时去抖动
					if(1 == btn_.DigitalRead()){ 
						while(!btn_.DigitalRead());
						SetColor("makeroboGREEN");
						cout << "No Button is pressed!" << endl;
					}
				}
			}
		}

	}
private:
	Gpio btn_{makerobo_BtnPin};

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
