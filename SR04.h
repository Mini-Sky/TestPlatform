#ifndef __SR04_H
#define __SR04_H
#include <Arduino.h>

class SR04
{
  public:
    SR04(uint8_t trig_pin, uint8_t echo_pin);
    void Init();
    float GetDistance();
    void InteruptProcess();
    void StateUpdate();
    
  private:
    uint8_t Trig_Pin;
    uint8_t Echo_Pin;
    
    bool IsTesting;
    bool IsTestingFinished;
    uint32_t StartTime;
    uint32_t LoopTime;
    float Distance;
};
#endif
