#include <Servo.h> 
Servo myservo;  
int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor
int degree=0;
void setup() {
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin); //获取电位器的电平数据
  Serial.println(sensorValue);
  degree = map(sensorValue, 0, 1023, 0, 180); //将电位器的电平数据范围对应到旋转角度的范围
  myservo.write(degree); //写入转换后的旋转角度
}
