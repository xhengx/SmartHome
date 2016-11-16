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
#include <BH1750FVI.h> //阳光强度感应
#include <Wire.h>
#include <dht11.h>

//使用JSON来向外传输传感器数据,做到平台通用
/*
 data:{
    "tempture": 30.3
    "humidity": 0.85
    "sun_light": 900
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
        接收请求，解析并且返回对应的结果,
        如果请求为request_sensors,返回data的JSON字符串
     */
    String recive_request(String jsonStr);
    
    
private:
    SensorsData request_sensors_data();
    void set_sensors(SensorsData data);
    
    int read_leds_state() ;
    void set_leds_state(int state) ;
    
    int read_rain_state() ;
    void set_rain_state(int state);
    
    int read_fans_state() ;
    void set_fans_state(int state);
    
    int read_wet_state() ;
    void set_wet_state(int state) ;
    
    int read_curtain_state() ;
    void set_curtain_state(int state) ;
    
    int read_tempture_state() ;
    void set_tempture_state(int state) ;
    
    int read_humidity_state() ;
    void set_humidity_state(int state) ;
    
    int read_sun_light_state() ;
    void set_sun_light_state(int state) ;
    
    float read_tempture_value() ;
    float read_humidity_value() ;
    float read_sun_light_value() ;
};

#endif /* HomeSensors_h */
