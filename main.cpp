// note
// mode : HZ : T
// 0    : 5  : 200 ms
// 1    : 10 : 100 ms
// 2    : 50 : 20  ms
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);  // serial tx, serial rx, reset pin;

DigitalIn BtnSelect(D10);
DigitalIn BtnUp(D11);
DigitalIn BtnDown(D12);

DigitalOut Writing(LED2);

AnalogOut WaveOut(D13);
AnalogIn WaveIn(D7);

int nowType, nowSelect, WaveType, sample;
double increaseDelta, decreaseDelta, data[1300];
const int S = 9;

void uLCDControl(void);
void uLCDInit(void);
bool BtnControl(void);
void Init(void);
bool WaveGen(void);
void ShowData(void);
void Reset(void);
int main(void) {
    int temp;
    Init();
    while(1) {
        Reset();
        while(1) {
            temp = BtnControl();
            if (temp) break;
        }
        while(1) {
            temp = WaveGen();
            if (temp) {
                break;
            }
        }
        Writing = 1;
        ShowData();
    }
    return 0;
}
void uLCDControl(void) {
    uLCD.locate(3,1);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.color(0x00FF00);
    uLCD.printf("5HZ");

    uLCD.locate(3,3);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.color(0x00FF00);
    uLCD.printf("10HZ");

    uLCD.locate(3,5);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.color(0x00FF00);
    uLCD.printf("50HZ");

    uLCD.locate(3,1 + nowType*2);
    uLCD.textbackground_color(0xFFFFFF * nowSelect);
    uLCD.color(0xFF00FF);

    if (nowType == 0) {
        uLCD.printf("5HZ");
    } else if (nowType == 1) {
        uLCD.printf("10HZ");
    } else if (nowType == 2) {
        uLCD.printf("50HZ");
    }
}
void uLCDInit(void) {
    uLCD.background_color(0xFFFFFF);
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.cls();
}
bool BtnControl(void) {
    if (BtnSelect) {
        nowSelect = 1;
        WaveType = nowType;
        uLCDControl();
    } else if (BtnUp) {
        nowType = nowType == 2 ? 0 : nowType+1;
        nowSelect = 0;
        uLCDControl();
    } else if (BtnDown) {
        nowType = nowType == 0 ? 2 : nowType-1;
        nowSelect = 0;
        uLCDControl();
    } else {
        nowSelect = 0;
    }

    return nowSelect;
}
void Init(void) {
    nowType = 1;
    nowSelect = 0;
    WaveType = nowType;
    increaseDelta = 1.0 / 90;
    decreaseDelta = 1.0 / 10;
    sample = 0;
    Writing = 0;
    uLCDInit();
}
bool WaveGen(void) {
    if (WaveType == 0) {
        increaseDelta = 1.0 / 180;
        decreaseDelta = 1.0 / 20;
    } else if (WaveType == 1) {
        increaseDelta = 1.0 / 90;
        decreaseDelta = 1.0 / 10;
    } else if (WaveType == 2) {
        increaseDelta = 1.0 / 18;
        decreaseDelta = 1.0 / 2;
    }
    for (double i=0; i<1; i+= increaseDelta) {
        WaveOut = i;
        ThisThread::sleep_for(1ms);
        data[sample++] = WaveIn;
    }
    for (double i=1; i>0; i-= decreaseDelta) {
        WaveOut = i;
        ThisThread::sleep_for(1ms);
        data[sample++] = WaveIn;
    }
    return sample > 1000;
}
void ShowData(void) {
    for (int i=0; i<1000; i++) {
        printf("%lf\n", data[i]);
    }
}
void Reset(void) {
    nowSelect = 0;
    Writing = 0;
    sample = 0;
    uLCDControl();
}

