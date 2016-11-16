//
//  HomeSensors.cpp
//  
//
//  Created by honey on 14/11/2016.
//
//

#include "HomeSensors.h"
#include "SensorsData.h"
#include "Sensors.h"
#include "Common.h"
Sensors sensors;

String parseSensorsDataToJSON(SensorsData data) {

  DynamicJsonBuffer  jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  
  root["tempture"] = data.tempture;
  root["humidity"] = data.humidity;
  root["sun_light"] = data.sun_light;
  root["rain_level"] = data.rain_level;
  root["flower_wet_level"] = data.wet_level;
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
  
  sensors.set_leds_state(data.light_on);
  sensors.set_rain_state(data.fans_on);
  sensors.set_fans_state(data.fans_on);
  sensors.set_wet_state(data.flower_wet_on);
  sensors.set_curtain_state(data.curtain_on);
  sensors.set_tempture_state(data.tempture_on);
  sensors.set_humidity_state(data.humidity_on);
  sensors.set_sun_light_state(data.sun_light_on);

  info("设置传感器结束...");
}

SensorsData HomeSensors::request_sensors_data() {
  info("开始获取传感器数据...");
  SensorsData data;
  data.tempture = sensors.read_tempture_value();
  data.humidity = sensors.read_humidity_value();
  data.sun_light = sensors.read_sun_light_value();
  data.rain_level = sensors.read_rain_level();
  data.wet_level = sensors.read_wet_level();
  data.rain_on = sensors.read_rain_state();
  data.fans_on = sensors.read_fans_state();
  data.curtain_on = sensors.read_curtain_state();
  data.flower_wet_on = sensors.read_wet_state();
  data.light_on = sensors.read_leds_state();
  data.sun_light_on = sensors.read_sun_light_state();
  data.humidity_on = sensors.read_humidity_state();
  data.tempture_on = sensors.read_tempture_state();
  info("获取传感器数据结束...");
  return data;
}









