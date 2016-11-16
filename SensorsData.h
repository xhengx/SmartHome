//
//  SensorsData.hpp
//
//
//  Created by honey on 16/11/2016.
//
//

#ifndef SensorsData_h
#define SensorsData_h

#include <stdio.h>

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
#endif /* SensorsData_hpp */
