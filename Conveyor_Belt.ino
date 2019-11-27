#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensor, pass=0,fail=0,state=0;
void setup() {
  myservo.attach(6);
  // put your setup code here, to run once:
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Conveyor System");
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,INPUT);
  Serial.begin(9600);
  myservo.write(120);
  delay(500);
  myservo.write(50);
  delay(500);
  myservo.write(180);
  

}

void loop() {
  if(digitalRead(12))
  state = !state;
  delay(100);
  Serial.println(state);
  
  // put your main code here, to run repeatedly:
  belt(state);
//  Serial.println(analogRead(A0));
//  delay(100);
  sensor = analogRead(A0)>900;
  lcd.setCursor(0,1);
  lcd.print("Rejected: ");
  lcd.print(fail);
  if(!sensor)
  {
    fail++;
    sensor = analogRead(A0)>900;
    while(!sensor)
    {
      sensor = analogRead(A0)>900;
//      belt(1);
    
    }
    belt(0);
    delay(10);
    myservo.write(0);
    delay(500);
    myservo.write(180);
    belt(1);
  }
//  Serial.println(fail);
//  delay(200);
}


void belt(bool value)
{
  if(value)
  {
  digitalWrite(2,1);
  digitalWrite(4,0);
  analogWrite(11,120);
  }
  else
  {
  digitalWrite(2,0);
  digitalWrite(4,0);
  analogWrite(11,180);
    }
}

