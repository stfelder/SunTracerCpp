//
// Created by stefanfelder on 25.03.2024.
//

#ifndef GOOGLETEST_CALCULATOR_H
#define GOOGLETEST_CALCULATOR_H

#include <cmath>

class SunTracer {
public:
    double getAltitue_Degress(double latitude, double declination, double hourAngle_hour);
    double getAltitue_Degress(double latitude_Degress, double longitude_Degress, int year, int month, int day, int hour_UTC, int minute, int second);

    double getJulianDate_FROM_UTC(int year, int month, int day, int hour, int minute, int second);
    double getGMST(double julianDate);
    double getLocalSiderealTime(double gmst, double longitude_Degress);
    double getSunDeclination_Degress(double julianDate);
    double getHourAngle_Degress(double localSiderealTime, double rightAscension);

    double getSunRightAscension(double julianDate);

    double calculateSunAzimuth(double latitude_Degress, double declination_Degress, double hourAngle_Degress);


    double calculateSunAzimuth(double latitude_Degress, double longitude_Degress, int year, int month, int day, int hour_UTC, int minute, int second);


private:
    double getSunTrueLongitude(double julianDate);

    const double degToRad = M_PI / 180.0;


};
#endif //GOOGLETEST_CALCULATOR_H
