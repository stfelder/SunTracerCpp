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

    double calculate_sun_azimuth_in_degrees(double latitude_Degrees, double longitude_Degrees, int year, int month, int day, int hour_UTC, int minute, int second);
    double calculate_sun_azimuth_in_degrees(double latitude, double declination, std::time_t time_UTC);
    double calculate_sun_azimuth_From_Current_Systemtime_in_degrees(double latitude_Degrees, double longitude_Degrees);


    double calculate_sun_altitude_in_degrees(double latitude_Degrees, double longitude_Degrees, int year, int month, int day, int hour_UTC, int minute, int second);
    double calculate_sun_altitude_in_degrees(double latitude, double declination, std::time_t time_UTC);
    double calculate_sun_altitude_From_Current_Systemtime_in_degrees(double latitude_Degrees, double longitude_Degrees);

private:
    [[nodiscard]] double getSunTrueLongitude(double julianDate) const;

    static double getJulianDate_FROM_UTC(int year, int month, int day, int hour_UTC, int minute, int second);
    static double getGMST(double julianDate);
    static double getLocalSiderealTime(double gmst, double longitude_Degrees);
    static double getSunDeclination_Degrees(double julianDate);
    static double getHourAngle_Degrees(double localSiderealTime, double rightAscension);
    double getSunRightAscension(double julianDate);
    static double calculate_sun_altitude_in_degrees(double latitude, double declination, double hourAngle_hour);
    static double calculate_sun_azimuth_in_degrees(double latitude_Degrees, double declination_Degrees, double hourAngle_Degrees);

    constexpr static const double degToRad = M_PI / 180.0;
    constexpr static const double radToDeg = 180.0 / M_PI;
    constexpr static const double J2000 = 2451545.0; // Julianische Tageszahl des 1.1.2000, 12:00 Uhr


};
#endif //GOOGLETEST_CALCULATOR_H
