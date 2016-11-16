//
//  Sensors.cpp
//  
//
//  Created by honey on 16/11/2016.
//
//

#include "Sensors.h"
#include "Common.h"
#include <BH1750FVI.h> //阳光强度感应
#include <Wire.h>
#include <dht11.h>

BH1750FVI light_sensor; //范围 1 - 65535
dht11   DHT11; //温湿度传感器

//传感器引脚定义
#define DHT11PIN 2
#define RAINPIN  A0

#define On    true
#define Off   false

#define RAIN_SENSOR_MIN 0     // 值越小,雨量越大
#define RAIN_SENSOR_MAX 1024  // 值越大,雨量最小





//温湿度相关转换函数
double Fahrenheit(double celsius);
double Kelvin(double celsius);
double dewPoint(double celsius, double humidity);
double dewPointFast(double celsius, double humidity);

// 设置获取led状态
int Sensors::read_leds_state() {
    return 1;
}
void Sensors::set_leds_state(int state) {
   if (state == On) {
      info("打开led灯");
   }
   else {
      info("关闭led灯");
   }
}
// 设置获取雨水感应器状态
int Sensors::read_rain_state() {
    return 0;
}
void Sensors::set_rain_state(int state) {
   if (state == On) {
      info("打开雨水感应传感器");
   }
   else {
      info("关闭雨水感应传感器");
   }
}
int Sensors::read_rain_level() {
  int sensorReading = analogRead(RAINPIN);
  //将雨水值映射为三个等级,0 大雨, 1 有雨, 2 没雨
  int range = map(sensorReading, RAIN_SENSOR_MIN, RAIN_SENSOR_MAX, 0, 3); 
  
  return range;
}

// 设置获取风扇状态
int Sensors::read_fans_state() {
    return 0;
}
void Sensors::set_fans_state(int state) {
   if (state == On) {
      info("打开风扇");
   }
   else {
      info("关闭风扇");
   }
}

// 设置获取土壤湿度应器状态
int Sensors::read_wet_state() {
    return 0;
}
void Sensors::set_wet_state(int state) {
   if (state == On) {
      info("打开植物土壤湿度传感器");
   }
   else {
      info("关闭植物土壤湿度传感器");
   }
}
// 设置获取窗帘状态
int Sensors::read_curtain_state() {
    return 0;
}

void Sensors::set_curtain_state(int state) {

   if (state == On) {
      info("打开窗帘");
   }
   else {
      info("关闭窗帘");
   }
}
// 设置获取温度感应器状态
int Sensors::read_tempture_state() {
    return 0;
}
void Sensors::set_tempture_state(int state) {
   if (state == On) {
      info("打开温度传感器");
   }
   else {
      info("关闭温度传感器");
   }
}
// 设置获取湿度感应器状态
int Sensors::read_humidity_state() {
    return 0;
}
void Sensors::set_humidity_state(int state) {
   if (state == On) {
      info("打开湿度传感器");
   }
   else {
      info("关闭湿度传感器");
   }
}
// 设置获取阳光感应器状态
int Sensors::read_sun_light_state() {
    return 1;
}
void Sensors::set_sun_light_state(int state) {
   if (state == On) {
      info("打开阳光强度感应传感器");
   }
   else {
      info("关闭阳光强度感应传感器");
   }
}

// 获取温度值
float Sensors::read_tempture_value() {
  DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}
// 获取湿度值
float Sensors::read_humidity_value() {
  DHT11.read(DHT11PIN);
  return (float)DHT11.humidity;
}
// 获取阳光值
float Sensors::read_sun_light_value() {
    info("获取阳光强度");
    light_sensor.begin();
    light_sensor.SetAddress(Device_Address_H);
    light_sensor.SetMode(OneTime_H_resolution_Mode);
    uint16_t lux = light_sensor.GetLightIntensity();// Get Lux value
    return lux;
}

//
double Fahrenheit(double celsius) 
{
        return 1.8 * celsius + 32;
}    //摄氏温度度转化为华氏温度

double Kelvin(double celsius)
{
        return celsius + 273.15;
}     //摄氏温度转化为开氏温度

// 露点（点在此温度时，空气饱和并产生露珠）
// 参考: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

// 快速计算露点，速度是5倍dewPoint()
// 参考: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}
//
