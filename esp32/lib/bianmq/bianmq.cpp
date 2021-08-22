#include "Arduino.h"
#include "bianmq.h"
int clk,dt,sw;
int aLastState;
int bLastState;
int SWLastState;
bianmq::bianmq(int CLK,int DT,int SW)
{
     clk=CLK;
     dt=DT;
     sw=SW;
}
void bianmq::init()
{
  pinMode(clk,INPUT);
  pinMode(dt,INPUT);
  pinMode(sw,INPUT_PULLUP);
  aLastState = digitalRead(clk);
  bLastState = digitalRead(dt);
  SWLastState = digitalRead(sw);
}
bianmq_ bianmq::bianmq_state()
{
    int SWState,aState,bState;
    SWState = digitalRead(sw); // 按钮输出状态
    aState = digitalRead(clk); // CLK的输出状态0/1
    bState = digitalRead(dt); // DT的输出状态0/1
    if (aState != aLastState){ //变化检测
        delay(50);//消抖
        if (aState != bState) { // 如果A!=B，则表示编码器正在顺时针旋转
        return Forward_rotation;
        } 
        else{ // 如果A=B，则表示编码器正在逆时针旋转
        return inverse_rotation;
        }

    }
    if(SWLastState!=SWState)
    {
        return confirm;
    }
  /*Serial.printf("%d %d %d  ",sw,clk,dt);
    Serial.print("num: ");
    Serial.print(aState);
    Serial.print(" ");
    Serial.println(bState);*/
   // return (bianmq_)4;

    
    //  Serial.print("nowSW: ");
    //  Serial.println(SWState);
    aLastState = aState;
    SWLastState = SWState;
}