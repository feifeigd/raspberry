
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


int clb_tmp = 0; // 比较值

class Application: public base::Application{
public:
	bool init()override{
		// 输入模式
		btn_.PinMode(INPUT);

		// 设置为输出模式
		red_.PinMode(OUTPUT);
		green_.PinMode(OUTPUT);

		// SetColor("makeroboGREEN");

		return true;
	}

	// 
	void SetColor(int color){
		// 设置为输出模式
		red_.PinMode(OUTPUT);
		green_.PinMode(OUTPUT);
		if(0 == color){	// 点亮红色
			red_.DigitalWrite(HIGH);
			green_.DigitalWrite(LOW);
			cout << "red" << endl;
		}else if(1== color){  // 点亮绿色
			red_.DigitalWrite(LOW);
			green_.DigitalWrite(HIGH);
			cout << "green" << endl;
		}else cerr << "makerobo Double color LED Error!" << endl;
	}
	void print(int x){
		if(x != clb_tmp){
			if(0 == x)
				cout << "...Makerobo ON" << endl;
			if(1 == x)
				cout << "...Makerobo OFF" << endl;
			clb_tmp = x;
		}
	}
	void loop(){
		int clb_status = 0; // 状态值
		int clb_value = 1; // 当前值

		while(true){
			clb_value = btn_.DigitalRead();
			if(clb_tmp != clb_value){ // 按钮按下
				if(++clb_status > 1)
					clb_status = 0;

				SetColor(clb_status);

				delay(100); // 延时去抖动
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
