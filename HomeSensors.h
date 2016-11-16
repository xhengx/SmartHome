//
//  HomeSensors.h
//  
//
//  Created by honey on 14/11/2016.
//
//

#ifndef HomeSensors_h
#define HomeSensors_h

#include <arduino.h> //包含整个arduino环境
#include <ArduinoJson.h> //arduino json解析库
#include "SensorsData.h"

//使用JSON来向外传输传感器数据,做到平台通用
/*
 data:{
    "tempture": 30.3
    "humidity": 0.85
    "sun_light": 900
    "rain_level": 2 //0 大雨, 1 有雨, 2 没雨
    "rain_on": false
    "fans_on": false
    "curtain_on": true
    "flower_wet_on": false
    "light_on":  false
 }
*/

//使用JSON来接收外部传输的设置,简化数据发送
/*
 rquest:{
    "request_sensors" : true //请求data,返回所有传感器数据
    "request_control" : true //请求设置control,
     "control":{
          "set_rain_on" : false
          "set_fans_on" : true
          "set_curtain_on" : false
          "set_flower_wet_on" : true
          "set_light_on" : true
          "set_tempture_on" : true
          "set_humidity_on" : true
          "set_sun_light_on" : true
      }
 }
 //返回操作结果,结果同data
*/
class SensorsData; //传感器数据对象

class HomeSensors {
    
public:
    /*
        接收请求，解析并且返回对应的结果,结果返回dataJSON字符串
     */
    String recive_request(String jsonStr);
    
private:
    SensorsData request_sensors_data();
    void set_sensors(SensorsData data);
};

#endif /* HomeSensors_h */
