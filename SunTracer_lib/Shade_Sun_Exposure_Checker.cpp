//
// Created by stefanfelder on 16.04.2024.
//

#include "Shade_Sun_Exposure_Checker.h"


bool Shade_Sun_Exposure_Checker::is_now_sun_shining_on_shade( double shade_azimuth, double latitude, double longitude){
    // Hole die aktuelle Zeit als time_point
    auto now = std::chrono::system_clock::now();

    // Konvertiere time_point zu time_t, um mit der C Standardbibliothek zu arbeiten
    time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Konvertiere time_t zu tm als UTC
    std::tm* now_tm = std::gmtime(&now_c);

    // Tag, monat und Jahr auslesen
    int year_now = now_tm->tm_year + 1900;
    int month_now = now_tm->tm_mon + 1;
    int day_now = now_tm->tm_mday;
    int hour_now = now_tm->tm_hour;
    int minute_now = now_tm->tm_min;
    int second_now = now_tm->tm_sec;

    double sun_azimuth = _sunTracer.calculate_sun_altitude_in_degrees(latitude, longitude,
                                                                      year_now, month_now, day_now,
                                                                      hour_now, minute_now, second_now);
    double sun_altitude = _sunTracer.calculate_sun_azimuth_in_degrees(latitude, longitude,
                                                                      year_now, month_now, day_now,
                                                                      hour_now, minute_now, second_now);

    bool is_sun_shining = is_sun_shining_on_shade(shade_azimuth, year_now, month_now, day_now,
                                                  hour_now, minute_now, second_now,
                                                  sun_altitude, sun_azimuth);

    return is_sun_shining;
}

bool Shade_Sun_Exposure_Checker::is_sun_shining_on_shade(double shade_azimuth,
                                                         int year, int month, int day, int hour_UTC, int minute,
                                                         int second, double latitude, double longitude,
                                                         double shade_direction_tolerance_start_in_deg,
                                                         double shade_direction_tolerance_end_in_degrees) {

    double sun_azimuth = _sunTracer.calculate_sun_azimuth_in_degrees(latitude, longitude,
                                                                     year, month, day, hour_UTC, minute, second);

    double sun_altitude = _sunTracer.calculate_sun_altitude_in_degrees(latitude, longitude,
                                                                      year, month, day, hour_UTC, minute, second);

    //Check if sun is shining on shade
    if (sun_azimuth > shade_azimuth - 90.0 + shade_direction_tolerance_start_in_deg
    && sun_azimuth < shade_azimuth + 90.0 - shade_direction_tolerance_end_in_degrees
    && sun_altitude > 0.0) {
        return true;
    }
    return false;
}

bool is_sun_shining_on_shade(double sun_altitude, double sun_azimuth, double shade_azimuth, double shade_direction_tolerance_start_in_deg, double shade_direction_tolerance_end_in_degrees){
    //Check if sun is shining on shade
    if (sun_azimuth > shade_azimuth - 90.0 + shade_direction_tolerance_start_in_deg
    && sun_azimuth < shade_azimuth + 90.0 - shade_direction_tolerance_end_in_degrees
    && sun_altitude > 0.0) {
        return true;
    }
    return false;
}

bool Shade_Sun_Exposure_Checker::is_now_sun_shining_on_shade(double shade_azimuth, double latitude, double longitude) {
    double sun_azimuth = _sunTracer.calculate_sun_azimuth_From_Current_Systemtime_in_degrees(latitude, longitude);
    double sun_altitude = _sunTracer.calculate_sun_altitude_From_Current_Systemtime_in_degrees(latitude, longitude);



    return false;
}
