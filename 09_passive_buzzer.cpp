
#include <Application.h>
#include <Gpio.h>

#include <iostream>

#define ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

using namespace std;
typedef unsigned char uchar;

enum{
	makerobo_Led_PinRed = 0, // 红色LED灯引脚
};

// 音谱定义
// 低C音符低频率
enum Tone_CL: int{
	Tone_CL1 = 131,
	Tone_CL2 = 147,
	Tone_CL3 = 165,
	Tone_CL4 = 175,
	Tone_CL5 = 196,
	Tone_CL6 = 221,
	Tone_CL7 = 248,
};

// 中C音符低频率
enum Tone_CM: int{
	Tone_CM1 = 262,
	Tone_CM2 = 294,
	Tone_CM3 = 330,
	Tone_CM4 = 350,
	Tone_CM5 = 393,
	Tone_CM6 = 441,
	Tone_CM7 = 495,
};

// 高C音符低频率
enum Tone_CH: int{
	Tone_CH1 = 525,
	Tone_CH2 = 589,
	Tone_CH3 = 661,
	Tone_CH4 = 700,
	Tone_CH5 = 786,
	Tone_CH6 = 882,
	Tone_CH7 = 990,
};

// 无源蜂鸣器
class Application: public base::Application{
public:
	bool init()override{
		if(-1 == red_.SoftToneCreate()){
			cerr << "makerobo setup softTone failed!" << endl;
			return false;
		}
		return true;
	}

	void loop(){//return;
		while(true){
			cout << "makerobo music is being played..." << endl;
			// 播放第一首歌曲
			for(auto i = 0; i < ARRAY_COUNT(makerobo_song_1); ++i){
				red_.SoftToneWrite(makerobo_song_1[i]);
				delay(makerobo_beat_1[i] * 500);
			}
			
			cout << "play second music" << endl;
			// 播放第二首歌曲
			for(auto i = 0; i < ARRAY_COUNT(makerobo_song_2); ++i){
				red_.SoftToneWrite(makerobo_song_2[i]);
				delay(makerobo_beat_2[i] * 500);
			}
		}

	}
private:
	Gpio red_{makerobo_Led_PinRed};
	// 第一首歌曲的音谱
	int makerobo_song_1[31] = { 
		Tone_CM3, Tone_CM5, Tone_CM6, Tone_CM3, Tone_CM2,
		Tone_CM3, Tone_CM5, Tone_CM6, Tone_CH1, Tone_CM6,
		Tone_CM5, Tone_CM1, Tone_CM3, Tone_CM2, Tone_CM2,
		Tone_CM3, Tone_CM5, Tone_CM2, Tone_CM3, Tone_CM3,
		Tone_CL6, Tone_CL6, Tone_CL6, Tone_CM1, Tone_CM2, 
		Tone_CM3, Tone_CM2, Tone_CL7, Tone_CL6, Tone_CM1, 
		Tone_CL5,};
	// 第一首歌曲的节拍
	int makerobo_beat_1[35] = {
		1, 1, 3, 1, 1,
		3, 1, 1, 1, 1,
		1, 1, 1, 1, 3,
		1, 1, 3, 1, 1,
		1, 1, 1, 1, 1,
		2, 1, 1, 1, 1,
		1, 1, 1, 1, 3,
	};

	// 第二首歌曲的音谱
	int makerobo_song_2[30] = {
		Tone_CM1, Tone_CM1, Tone_CM1, Tone_CL5, Tone_CM3, 
		Tone_CM3, Tone_CM3, Tone_CM1, Tone_CM3, Tone_CM3, 
		Tone_CM5, Tone_CM5, Tone_CM4, Tone_CM3, Tone_CM2, 
		Tone_CM2, Tone_CM3, Tone_CM4, Tone_CM4, Tone_CM3, 
		Tone_CM2, Tone_CM3, Tone_CM1, Tone_CM1, Tone_CM3, 
		Tone_CM2, Tone_CL5, Tone_CM7, Tone_CM2, Tone_CM1, 
	};
	// 第二首歌曲的节拍
	int makerobo_beat_2[30] = {
		1, 1, 1, 3, 1, 
		1, 1, 3, 1, 1,
		1, 1, 1, 1, 3,
		1, 1, 1, 2, 1, 
		1, 1, 3, 1, 1,
		1, 3, 3, 2, 3,
	};
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
