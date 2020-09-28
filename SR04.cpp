#include "SR04.h"

SR04::SR04(uint8_t trig_pin, uint8_t echo_pin)
{
  Trig_Pin = trig_pin;
  Echo_Pin = echo_pin;
}

void SR04::Init()
{
  pinMode(Echo_Pin, INPUT);
  pinMode(Trig_Pin, OUTPUT);
}

float SR04::GetDistance()
{
  return Distance;
}

void SR04::StateUpdate()
{
  if(!IsTesting)
  {
    digitalWrite(Trig_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pin, LOW);
    IsTesting = true;
    IsTestingFinished = false;
  }
  else if(IsTestingFinished)
  {
    Distance = LoopTime * 17 / 1000;
    IsTesting = false;
  }
}
void SR04::InteruptProcess()
{
  if (digitalRead(Echo_Pin))
  {
    StartTime = micros();
  }
  else
  {
    LoopTime = micros() - StartTime;
    IsTestingFinished = true;
  }
}
