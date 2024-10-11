#include <SoftwareSerial.h>
#include <Servo.h>


// DS1302:  (RST)CE pin    -> Arduino Digital 2
//          (DAT)I/O pin   -> Arduino Digital 3
//          (CLK)SCLK pin  -> Arduino Digital 4

#include <DS1302.h>
#include <stdio.h>

// Init the DS1302
DS1302 rtc(2, 3, 4);//(R,D,C)
Time t;
Servo ser;
SoftwareSerial btSerial(10,9);
int a,b,c,i1,i2,i3;//a는 시, b는 분, c는 시*100+분
int k,i,m,z=0;//k,i,m과 z는 1,2,3번째 시간 때 울리는 부저 정지와 관련됨
String bt,ts,t1,t2,t3;
void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  btSerial.begin(9600);
  Serial.begin(9600);
  ser.attach(8);
  ser.write(0);
  pinMode(A0,OUTPUT);//부저
  pinMode(7,INPUT);//버튼 감지
  pinMode(6,OUTPUT);//버튼 전원 출력
  digitalWrite(6,HIGH);//버튼 전원 출력
  // 시간 입력해줌(한번만 해주고 다음부터는 주석 처리해야 함)
  //rtc.setTime(19, 42, 30);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(17, 11, 2019);   // Set the date to August 6th, 2010

  
}

void loop()
{
  t=rtc.getTime();//시간 얻어오기
  //Serial.println(t.hour);
  //Serial.println(t.min);
  a=t.hour;//시
  b=t.min;//분
  c=a*100+b;//시*100+분
  Serial.println(c);
  if(btSerial.available()){
    bt=btSerial.readString();
    ts=bt.substring(0,1);
  }
  if(ts=="1"){
    t1=bt.substring(1,5);
    i1=t1.toInt();
    if(c==i1){
      ser.write(55);
      if((z!=0) && (k==0)){
        z=0;
        k=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else{
      ser.write(0);
      z=0;
      k=0;
    }
  }
  if(ts=="2"){
    t1=bt.substring(1,5);
    t2=bt.substring(5,9);
    i1=t1.toInt();
    i2=t2.toInt();
    if(c==i1){
      ser.write(55);
      if((z!=0) && (k==0)){
        z=0;
        k=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else if(c==i2){
      ser.write(125);
      if((z!=0) && (i==0)){
        z=0;
        i=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else{
      ser.write(0);
      z=0;
      k=0;
      i=0;
    }
  }
  if(ts=="3"){
    t1=bt.substring(1,5);
    t2=bt.substring(5,9);
    t3=bt.substring(9,13);
    i1=t1.toInt();
    i2=t2.toInt();
    i3=t3.toInt();
    if(c==i1){
      ser.write(55);
      if((z!=0) && (k==0)){
        z=0;
        k=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else if(c==i2){
      ser.write(125);
      if((z!=0) && (i==0)){
        z=0;
        i=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else if(c==i3){
      ser.write(180);
      if((z!=0) && (m==0)){
        z=0;
        m=1;
      }
      else if(z==0){
        tone(A0,1000);
      }
      else if(z!=0){
        noTone(A0);
      }
    }
    else{
      ser.write(0);
      z=0;
      k=0;
      i=0;
      m=0;
    }
  }
  
  if(digitalRead(7)==HIGH){
    z++;//버튼 누르면 버저 꺼짐
  }
  
  
  //delay(1000);
}
