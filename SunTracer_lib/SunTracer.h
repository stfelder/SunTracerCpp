//
// Created by stefanfelder on 25.03.2024.
//

#ifndef GOOGLETEST_CALCULATOR_H
#define GOOGLETEST_CALCULATOR_H

#include <cmath>
#include <chrono>
#include <ctime>

class SunTracer {
public:






    double calculate_sun_azimuth_in_degress(double latitude_Degress, double longitude_Degress, int year, int month, int day, int hour_UTC, int minute, int second);
    double calculate_sun_azimuth_in_degress(double latitude, double declination, std::time_t time_UTC);



    double calculate_sun_altitue_in_degress(double latitude_Degress, double longitude_Degress, int year, int month, int day, int hour_UTC, int minute, int second);
    double calculate_sun_altitue_in_degress(double latitude, double declination, std::time_t time_UTC);




private:
    double getSunTrueLongitude(double julianDate);

    double getJulianDate_FROM_UTC(int year, int month, int day, int hour_UTC, int minute, int second);
    double getGMST(double julianDate);
    double getLocalSiderealTime(double gmst, double longitude_Degress);
    double getSunDeclination_Degress(double julianDate);
    double getHourAngle_Degress(double localSiderealTime, double rightAscension);
    double getSunRightAscension(double julianDate);
    double calculate_sun_altitue_in_degress(double latitude, double declination, double hourAngle_hour);
    double calculate_sun_azimuth_in_degress(double latitude_Degress, double declination_Degress, double hourAngle_Degress);

    const double degToRad = M_PI / 180.0;


};
#endif //GOOGLETEST_CALCULATOR_H
