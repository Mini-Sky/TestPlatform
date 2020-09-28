#include "SR04.h"
#include "Pins_Def.h"
#include <Servo.h>
#include <MsTimer2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SR04 sr04(Trig_Pin, Echo_Pin);  //实例化对象
Servo myservo;

uint8_t angle = 0;//角度参数
uint32_t RGB_Time = 0;
uint8_t RGB_State = 0;
int8_t EC_Val = 0;
void RpControlServo();          //电位器控制舵机函数

uint8_t select_value = 0;
bool time_state = 1;
uint32_t old_times = 0;
void setup()
{
  //Serial.begin(115200);
  myservo.attach(ServoPin);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(RP, INPUT_PULLUP);

  pinMode(HW_Pin, INPUT_PULLUP);
  pinMode(LT_Pin, INPUT_PULLUP);

  pinMode(FourTrack_PinX1, INPUT_PULLUP);
  pinMode(FourTrack_PinX2, INPUT_PULLUP);
  pinMode(FourTrack_PinX3, INPUT_PULLUP);
  pinMode(FourTrack_PinX4, INPUT_PULLUP);

  pinMode(ThreeTrack_PinX1, INPUT_PULLUP);
  pinMode(ThreeTrack_PinX2, INPUT_PULLUP);
  pinMode(ThreeTrack_PinX3, INPUT_PULLUP);

  pinMode(RGB_PinR, OUTPUT);
  pinMode(RGB_PinG, OUTPUT);
  pinMode(RGB_PinB, OUTPUT);

  pinMode(Encoder_PinA, INPUT);
  pinMode(Encoder_PinB, INPUT);

  sr04.Init();
  attachInterrupt(Echo_INT, Echo_ChangeEvent, CHANGE);
  MsTimer2::set(3, Encoder_Update);
  MsTimer2::start();
}

void loop()
{
  sr04.StateUpdate();
  RpControlServo();
  OLED_Update();
  select_update();
  if (select_value >= 5)select_value = 0;
}
//超声波测距函数

void Echo_ChangeEvent()
{
  sr04.InteruptProcess();
}

void RpControlServo()
{
  uint32_t sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sum += analogRead(RP);
  }
  angle = map(sum / 10, 0, 1024, 0, 180);
  myservo.write(angle);
}

void OLED_Update(void)
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 1);
  display.print('A');
  display.setCursor(20, 1);
  display.print('B');
  display.setCursor(35, 1);
  display.print('C');
  display.setCursor(50, 1);
  display.print('D');
  display.setCursor(65, 1);
  display.print('E');
  display.setCursor(80, 1);
  display.print('F');
  display.setCursor(95, 1);
  display.print('G');
  display.setCursor(110, 1);
  display.print('H');

  display.drawRect(3 + 15 * select_value, 0, 14, 16, WHITE);

  if (select_value == 0)
  {
    display.setTextSize(2);
    display.setCursor(5, 18);
    display.print(F("Dist:"));
    display.print((int)sr04.GetDistance());
    display.print(F("cm"));
  }
  else if (select_value == 1)
  {
    display.setCursor(5, 18);
    display.print(F("RP:"));
    display.print(angle);
    RpControlServo();
  }
  else if (select_value == 2)
  {
    display.setCursor(5, 18);
    display.print(F("F_T:"));
    display.print(digitalRead(FourTrack_PinX2));
    display.print(digitalRead(FourTrack_PinX1));
    display.print(digitalRead(FourTrack_PinX3));
    display.print(digitalRead(FourTrack_PinX4));
  }
  else if (select_value == 3)
  {
    display.setCursor(5, 18);
    display.print(F("HW:"));
    display.setCursor(42, 18);
    display.print(digitalRead(HW_Pin));
    display.setCursor(66, 18);
    display.print(F("LT:"));
    display.setCursor(108, 18);
    display.print(digitalRead(LT_Pin));
  }
  else if (select_value == 4)
  {
    display.setCursor(5, 18);
    display.print(F("RGBPLAYING"));
    RGB_PLAY();
  }



  //  //超声波测距显示 第一行
  //  display.setCursor(2, 2);
  //  display.print(F("Distance:"));
  //  display.setCursor(55, 2);
  //  display.print((int)sr04.GetDistance());
  //  display.setCursor(73, 2);
  //  display.print(F("cm"));
  //  //电位器控制舵机旋转角度 第一行
  //  display.setCursor(90, 2);
  //  display.print(F("RP:"));
  //  display.setCursor(108, 2);
  //  display.print(angle);
  //
  //  //四路循迹模块
  //  display.setCursor(2, 12);
  //  display.print(F("F_Trck:"));
  //  display.setCursor(43, 12);
  //  display.print(digitalRead(FourTrack_PinX2));
  //  display.setCursor(50, 12);
  //  display.print(digitalRead(FourTrack_PinX1));
  //  display.setCursor(57, 12);
  //  display.print(digitalRead(FourTrack_PinX3));
  //  display.setCursor(64, 12);
  //  display.print(digitalRead(FourTrack_PinX4));
  //
  //  //红外寻光避障模块
  //  display.setCursor(73, 12);
  //  display.print(F("HW:"));
  //  display.setCursor(90, 12);
  //  display.print(digitalRead(HW_Pin));
  //  display.setCursor(100, 12);
  //  display.print(F("LT:"));
  //  display.setCursor(117, 12);
  //  display.print(digitalRead(LT_Pin));
  //
  //  //三路灰度传感器
  //  display.setCursor(2, 22);
  //  display.print((F("T_Trck:")));
  //  display.setCursor(43, 22);
  //  display.print(analogRead(ThreeTrack_PinX1));
  //  display.setCursor(70, 22);
  //  display.print(analogRead(ThreeTrack_PinX2));
  //  display.setCursor(97, 22);
  //  display.print(analogRead(ThreeTrack_PinX3));
  //
  //  display.drawRect(0, 0, 128, 32, SSD1306_WHITE);
  display.display();
}

void RGB_PLAY()
{
  Serial.print(RGB_State);
  if (millis() - RGB_Time > 1000)
  {
    if (RGB_State == 0)
    {
      digitalWrite(RGB_PinR, HIGH);
      digitalWrite(RGB_PinG, LOW);
      digitalWrite(RGB_PinB, LOW);
      RGB_State = 1;
      RGB_Time = millis();

    }
    else if (RGB_State == 1)
    {
      digitalWrite(RGB_PinR, LOW);
      digitalWrite(RGB_PinG, HIGH);
      digitalWrite(RGB_PinB, LOW);
      RGB_State = 2;
      RGB_Time = millis();
    }
    else if (RGB_State == 2)
    {
      digitalWrite(RGB_PinR, LOW);
      digitalWrite(RGB_PinG, LOW);
      digitalWrite(RGB_PinB, HIGH);
      RGB_State = 0;
      RGB_Time = millis();
    }
  }
}
void Encoder_Update()
{
  bool A_State = digitalRead(Encoder_PinA);
  bool B_State = digitalRead(Encoder_PinB);
  Serial.println(B_State);
  static bool A_State_Last;
  if (A_State == 1 && A_State_Last == 0)
  {
    Encoder_Event(B_State);
  }
  A_State_Last = A_State;
}
void Encoder_Event(bool state)
{
  EC_Val += (state ? -1 : 1);
  EC_Val = constrain(EC_Val, 0, 7);
}
void select_update()
{
  if (delay_ms(5000))select_value++;
}
bool delay_ms(uint16_t times)
{
  if (time_state)
  {
    old_times = millis();
    time_state = 0;
    return 0;
  }
  else if (millis() - old_times >= times)
  {
    time_state = 1;
    return 1;
  }
}
