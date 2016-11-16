//
//  HomeSensors.cpp
//  
//
//  Created by honey on 14/11/2016.
//
//

#include "HomeSensors.h"

#define DEBUG true
#define info(msg) if (DEBUG) { Serial.println(msg); }

#define On    true
#define Off   false

//BH1750FVI light_sensor; //范围 1 - 65535


class SensorsData {
public:
  //传感器数据
  float tempture;
  float humidity;
  float sun_light;
  //所有传感器默认关闭状态
  bool  rain_on       = false;
  bool  fans_on       = false;
  bool  curtain_on    = false;
  bool  flower_wet_on = false;
  bool  light_on      = false;
  bool  sun_light_on  = false;
  bool  humidity_on   = false;
  bool  tempture_on   = false;
};

String parseSensorsDataToJSON(SensorsData data) {

  DynamicJsonBuffer  jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  
  root["tempture"] = data.tempture;
  root["humidity"] = data.humidity;
//  root["sun_light"] = data.sun_light;
  
  root["rain_on"] = data.rain_on;
  root["fans_on"] = data.fans_on;
  root["curtain_on"] = data.curtain_on;
  root["flower_wet_on"] = data.flower_wet_on;
  root["light_on"] = data.light_on;
  root["sun_light_on"] = data.sun_light_on;
  root["tempture_on"] = data.tempture_on;
  root["humidity_on"] = data.humidity_on;

  String retString;
  //转换为字符串返回
  root.printTo(retString);

  if (data.light_on) {info("on");}
  info("string;;;;" + data.light_on);
  return retString;
}

SensorsData decode_sensors_data(JsonObject &root) {
  SensorsData data;
  data.rain_on = root["control"]["set_rain_on"].as<bool>();
  data.fans_on = root["control"]["set_fans_on"].as<bool>();
  data.curtain_on = root["control"]["set_curtain_on"].as<bool>();
  data.flower_wet_on = root["control"]["set_flower_wet_on"].as<bool>();
  data.light_on = root["control"]["set_light_on"].as<bool>();
  data.tempture_on = root["control"]["set_tempture_on"].as<bool>();
  data.humidity_on = root["control"]["set_humidity_on"].as<bool>();
  data.sun_light_on = root["control"]["set_sun_light_on"].as<bool>();
  return data;
}

//构造函数
HomeSensors::HomeSensors() {
  //初始化所有的传感器对象
}

void HomeSensors::init_light_sensor() {
  
}



String HomeSensors::recive_request(String jsonStr) {
    //开始json解析
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonStr);
    
    bool request_sensors = root["request_sensors"].as<bool>();
    bool request_control = root["request_control"].as<bool>();

    if (request_sensors) {
      info("请求传感器数据...");
    }
    else if (request_control) {
      info("请求设置传感器...");
      info("正在解析设置参数...");
      SensorsData data = decode_sensors_data(root);
      info("解析完毕");
      //设置传感器状态
      set_sensors(data);
    }
    //不管何种操作,最后都要将传感器数据回传给用户
    SensorsData data = request_sensors_data();
      //将读取到的传感器数据转换为JSON格式的字符串,并且返回
    return  parseSensorsDataToJSON(data);   
}

void HomeSensors::set_sensors(SensorsData data) {
  
  info("开始设置传感器...");

  set_leds_state(data.light_on);
  set_rain_state(data.fans_on);
  set_fans_state(data.fans_on);
  set_wet_state(data.flower_wet_on);
  set_curtain_state(data.curtain_on);
  set_tempture_state(data.tempture_on);
  set_humidity_state(data.humidity_on);
  set_sun_light_state(data.sun_light_on);

  info("设置传感器结束...");
}

SensorsData HomeSensors::request_sensors_data() {
  info("开始获取传感器数据...");
  SensorsData data;
  data.tempture = read_tempture_value();
  data.humidity = read_humidity_value();
  data.sun_light = read_sun_light_value();
  data.rain_on = read_rain_state();
  data.fans_on = read_fans_state();
  data.curtain_on = read_curtain_state();
  data.flower_wet_on = read_wet_state();
  data.light_on = read_leds_state();
  data.sun_light_on = read_sun_light_state();
  data.humidity_on = read_humidity_state();
  data.tempture_on = read_tempture_state();
  info("获取传感器数据结束...");
  return data;
}

// 设置获取led状态
int HomeSensors::read_leds_state() {
    return 1;
}
void HomeSensors::set_leds_state(int state) {
   if (state == On) {
      info("打开led灯");
   }
   else {
      info("关闭led灯");
   }
}
// 设置获取雨水感应器状态
int HomeSensors::read_rain_state() {
    return 0;
}
void HomeSensors::set_rain_state(int state) {
   if (state == On) {
      info("打开雨水感应传感器");
   }
   else {
      info("关闭雨水感应传感器");
   }
}
// 设置获取风扇状态
int HomeSensors::read_fans_state() {
    return 0;
}
void HomeSensors::set_fans_state(int state) {
   if (state == On) {
      info("打开风扇");
   }
   else {
      info("关闭风扇");
   }
}

// 设置获取土壤湿度应器状态
int HomeSensors::read_wet_state() {
    return 0;
}
void HomeSensors::set_wet_state(int state) {
   if (state == On) {
      info("打开植物土壤湿度传感器");
   }
   else {
      info("关闭植物土壤湿度传感器");
   }
}
// 设置获取窗帘状态
int HomeSensors::read_curtain_state() {
    return 0;
}

void HomeSensors::set_curtain_state(int state) {

   if (state == On) {
      info("打开窗帘");
   }
   else {
      info("关闭窗帘");
   }
}
// 设置获取温度感应器状态
int HomeSensors::read_tempture_state() {
    return 0;
}
void HomeSensors::set_tempture_state(int state) {
   if (state == On) {
      info("打开温度传感器");
   }
   else {
      info("关闭温度传感器");
   }
}
// 设置获取湿度感应器状态
int HomeSensors::read_humidity_state() {
    return 0;
}
void HomeSensors::set_humidity_state(int state) {
   if (state == On) {
      info("打开湿度传感器");
   }
   else {
      info("关闭湿度传感器");
   }
}
// 设置获取阳光感应器状态
int HomeSensors::read_sun_light_state() {
    return 1;
}
void HomeSensors::set_sun_light_state(int state) {
   if (state == On) {
      info("打开阳光强度感应传感器");
   }
   else {
      info("关闭阳光强度感应传感器");
   }
}

// 获取温度值
float HomeSensors::read_tempture_value() {
    return 0.0;
}
// 获取湿度值
float HomeSensors::read_humidity_value() {
    return 0.0;
}
// 获取阳光值
float HomeSensors::read_sun_light_value() {
    info("sun_light");
//    light_sensor.begin();
//    light_sensor.SetAddress(Device_Address_H);
//    light_sensor.SetMode(Continuous_H_resolution_Mode);
//    uint16_t lux = light_sensor.GetLightIntensity();// Get Lux value
//
//    info("lux----> " + lux);
    return 0.0;
}






