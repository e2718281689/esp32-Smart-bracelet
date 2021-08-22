#ifndef afxinlu
#define afxinlu

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "Arduino.h"

struct heartdate
{
    long IR;
    float BPM;
    int Avg_BPM;
    bool finger;
};

class xinlu
{
private:
    /* data */
    long irValue;
    float beatsPerMinute;
    int beatAvg;
public:

    xinlu();
    ~xinlu();
    heartdate heart_info;
    heartdate* heartRate();
    void Init();
};
#endif
