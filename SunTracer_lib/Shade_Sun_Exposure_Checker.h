//
// Created by stefanfelder on 16.04.2024.
//

#ifndef SUNTRACERCPP_SHADE_SUN_EXPOSURE_CHECKER_H
#define SUNTRACERCPP_SHADE_SUN_EXPOSURE_CHECKER_H

#include "SunTracer.h"


class Shade_Sun_Exposure_Checker {

public:
    bool is_sun_shining_on_shade(double shade_azimuth, int year, int month, int day, int hour_UTC,
                                 int minute, int second, double latitude, double longitude,
                                 double shade_direction_tolerance_start_in_deg = 5.0,
                                 double shade_direction_tolerance_end_in_deg = 5.0);

    bool is_now_sun_shining_on_shade(double shade_azimuth, double latitude, double longitude);

private:
    SunTracer _sunTracer{};


};



#endif //SUNTRACERCPP_SHADE_SUN_EXPOSURE_CHECKER_H
