//
//  Sensors.hpp
//
//
//  Created by honey on 16/11/2016.
//
//

#ifndef Sensors_h
#define Sensors_h

#include <stdio.h>

class Sensors {
  public:
    int read_leds_state() ;
    void set_leds_state(int state) ;

    int read_rain_state() ;
    void set_rain_state(int state);
    int read_rain_level();

    int read_fans_state() ;
    void set_fans_state(int state);

    int read_wet_state() ;
    void set_wet_state(int state) ;
    int read_wet_level();

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

#endif /* Sensors_hpp */
