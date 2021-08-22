#include "Arduino.h"
#ifndef _TEST_H_
#define _TEST_H_
typedef enum 
{
    Forward_rotation,
    inverse_rotation,
    confirm=2
}bianmq_;
//bianmq_ bianmq_tt;

class bianmq
{
private: 

public:
    int clk,dt,sw;
    int aLastState;
    int bLastState;
    int SWLastState;
    bianmq(int CLK,int DT,int SW);
    bianmq_ bianmq_state();
    void init();

};
#endif