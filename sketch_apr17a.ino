#include <Wire.h>


#include "C:\Users\Tien PC\Desktop\lib_pid.c"

#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F,16,2);

//ext in 2,3,21,20,19,18
#define  encoderPinA  2   // Tương ứng chân DT trên Encoder quay

#define  encoderPinB  3   // Tương ứng chân CLK trên Encoder quay

#define  encoderPinC  21   // Tương ứng chân CLK trên Encoder quay

#define  encoderPinD  20   // Tương ứng chân CLK trên Encoder quay


volatile  int encoderPos = 0;  // Cho vị trí đầu bằng 0

 int lastReportedPos = 1;   // Vị trí cuối bằng 1

//static boolean rotating=false;      // Quản lý debounce (giống như là chống nhiễu)

// các biến cho trình phục vụ ngắt interrupt service routine vars

boolean A_set = false;             

boolean B_set = false;


//Đo tốc độ

 int newposition;

 int oldposition=0;

 long newtime;

 long oldtime=0;

 int vantoc = 0;

 int ganvantoc = 0;

 int ganxung = 0;

 int sovong = 0;


volatile int xung =0 ;
PIDControl pid1;
PIDMode mode = AUTOMATIC;

int set_point = 1000;  //so xung quay trong 1 thoi gian 



void read_encoder_00(int& xung)
{
  xung = (digitalRead(3))? (xung++) : (xung--); 
}

/*void read_encoder_01(int& xung)
{
  xung = (digitalRead(4))? (xung++) : (xung--); 
}

void read_encoder_10(int& xung)
{
  xung = (digitalRead(5))? (xung++) : (xung--); 
}

void read_encoder_11(int& xung)
{
  xung = (digitalRead(7))? (xung++) : (xung--); 
}
*/

//interrupt timer 



 void setup() {
  lcd.begin(20,4);  
  lcd.init();                      // initialize the lcd

  lcd.backlight();

  pinMode(encoderPinA, INPUT_PULLUP); // INPUT-PULLUP tương đương Mode INPUT và tự động nhận trạng thái HIGH hoặc LOW
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);
    
attachInterrupt(0,read_encoder_00,RISING);
/*attachInterrupt(1,read_encoder_01,RISING);
attachInterrupt(2,read_encoder_10,RISING);
attachInterrupt(3,read_encoder_11,RISING);*/

 // Chân encoder trên ngắt 0 (chân 2)
  //attachInterrupt(0, doEncoderA, CHANGE);
// Chân encoder trên ngắt 1 (chân 3)
  //attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin(9600);  // chuyển dữ liệu lên cổng Serial Port

  lcd.setCursor(0,1);

  lcd.print("SO VONG = ");

   }

// Vòng lặp chính, công việc được thực hiện bởi trình phục vụ ngắt

void loop() {

   delay(1000);

   //rotating = true;  // Khởi động bộ debounce (có thể hiểu như bộ chống nhiễu)
   //thay the bang ngat timer cung duoc
   newtime=millis();
    error = set_point - xung;
   newposition=encoderPos;

   detachInterrupt(0);

   detachInterrupt(1);

   vantoc = (newposition-oldposition)*60/20;

    Serial.print("vantoc=");

    Serial.println(vantoc,DEC);

    oldposition=newposition;

    oldtime=newtime;

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("TOC DO  = ");

    lcd.setCursor(11,0);

    lcd.print(vantoc);

    lcd.print(" RPM");

    lcd.setCursor(0,1);

    lcd.print("SO VONG = ");

    lcd.setCursor(11,1);

    lcd.print(sovong,DEC);

    attachInterrupt(0, read_encoder_00, RISING);

    //attachInterrupt(1, doEncoderB, CHANGE); 
}

// Ngắt khi chuyển trạng thái của A
/*
void doEncoderA(){

  // debounce

  if ( rotating ) delay (1);  // Chờ 1 chút

  // Kiểm tra việc chuyển đổi trạng thái, xem có thật sự thay đổi trạng thái chưa

  if( digitalRead(encoderPinA) != A_set ) {  // debounce một lần nữa

    A_set = !A_set;

    // Cộng 1 nếu có tín hiệu A rồi có tín hiệu B       

    if ( A_set && !B_set )

      encoderPos += 1;

      ganxung += 1;

      sovong=encoderPos/20;

    if (ganxung == 42){ganxung=0;}

    rotating = false;  // Không cần debounce nữa cho đến khi được nhấn lần nữa

      }

  }

// Ngắt khi thay đổi trạng thái ở B, tương tự như ở A

void doEncoderB(){

  if ( rotating ) delay (1);

  if( digitalRead(encoderPinB) != B_set ) {

    B_set = !B_set;

    //  Trừ 1 nếu B rồi đến A

    if( B_set && !A_set )

      encoderPos -= 1;

      rotating = false;

  }
}*/
