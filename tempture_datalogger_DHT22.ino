/*
 * DHT22温湿度计
 * 西南交通大学工程训练中心
 */
//引入DHT22模块用的dht库
#include <dht.h>
//引入液晶模块使用的 liquid Crystal I2C库
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//初始化一个dht类型的实例
dht DHT;
//设置DHT22传感器传输数据使用的引脚
#define DHT22_PIN 5

//初始化一个液晶屏幕的实例,初始化时设置地址为0x3f（根据实际情况设置，国产常用0x27,0x3f），液晶尺寸为1602
LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup()
{
    Serial.begin(9600); //因为蓝牙模块的波特率通常是9600，所以设定为9600
    Serial.println("status,\tHumidity (%),\tTemperature (C)");
      //初始化液晶屏幕
    lcd.init();  // initialize the lcd
     
}

void loop()
{
    int chk = DHT.read22(DHT22_PIN);
  //检查是否有错误
  switch (chk)
  {
    case DHTLIB_OK:
    Serial.print("OK,\t");
    break;
    case DHTLIB_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
    case DHTLIB_ERROR_TIMEOUT:
    Serial.print("Time out error,\t");
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default:
    Serial.print("Unknown error,\t");
    break;
  }
   // 显示数据
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);
  //点亮背光
  lcd.backlight();
  //设置光标(x,y)(3就是第４个字符，０，就是第１行）
  lcd.setCursor(3,0);
  //在屏幕打印湿度
   lcd.print("HUMI:");
  lcd.print(DHT.humidity);
   //设置光标(x,y)(3就是第４个字符，1，就是第2行）
   lcd.setCursor(3,1);
  //在屏幕打印温度
  lcd.print("TEMP:");
  lcd.print(DHT.temperature);
  //延时２秒
  delay(2000);
  //清屏幕
  lcd.clear();
}

