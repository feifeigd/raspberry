
#include <Application.h>
#include <Gpio.h>

#include <iostream>

using namespace std;
typedef unsigned char uchar;

enum{
	makerobo_Led_RelayPin = 0, // 继电器引脚
};

class Application: public base::Application{
public:
	bool init()override{
		relay_.PinMode(OUTPUT);
		return true;
	}

	void loop(){
		while(true){
			relay_.DigitalWrite(HIGH); // 断开继电器
			delay(1000);

			relay_.DigitalWrite(LOW); // 关闭继电器
			delay(1000);
		}
	}
private:
	Gpio relay_{makerobo_Led_RelayPin}; // 继电器
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
