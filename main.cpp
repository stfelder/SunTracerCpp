#include <iostream>
#include "SunTracer.h"
#include "Shade_Sun_Exposure_Checker.h"

int main() {

    // Some initial values
    SunTracer sunTracer;

    double latitude = 47.0592;
    double longitude= 8.3013;
    int year = 2024; //Time in UTC
    int month = 4;
    int day = 16;
    int hour = 12;
    int minute = 57;
    int second = 0;


    /**************************************************************************
     *                    Exempel shading automation
     **************************************************************************/

    // Use the Shade_Sun_Exposure_Checker class to check if
    // the sun is shining on a shade at a specific location and time.
    // The shade is located at an azimuth of 180 degrees.
    // The location is Lucern, Switzerland on 29.03.2024 at 08:12:00 UTC.
    // Print the result to the console.

    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    double shaden_azimuth = 180.0;
    bool is_sun_shining = shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day, hour, minute, second, latitude, longitude);
    std::cout << "Is sun shining on shade: " << is_sun_shining << " (Time: "<< year << "." << month
              << "." << day << " " << hour << ":" << minute << ":" << second << ")"<<  std::endl;

    // Expected output:
    // Is sun shining on shade: 1

    // Use the Shade_Sun_Exposure_Checker class to check if
    // the sun is shining on a shade at a specific location and your system time.
    // The shade is located at an azimuth of 180 degrees.
    // The location is Lucern, Switzerland.
    // Print the result to the console.
    bool is_sun_shining_now = shadeSunExposureChecker.is_now_sun_shining_on_shade(shaden_azimuth, latitude, longitude);
    std::cout << "Is sun shining on shade now: " << is_sun_shining_now << std::endl;

    // Expected output:
    // Is sun shining on shade now: 1 or 0 -> depends on the current time
    //To verify the results, you can use the following website:
    //http://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/08:36/1/3


/**************************************************************************
 *         Exempel to calculate the sun's altitude and azimuth
 **************************************************************************/
    // Use the SunTracer class to calculate the sun's altitude and azimuth
    // for the Location Lucern, Switzerland on 29.03.2024 at 08:12:00 UTC
    // and print the results to the console.



    std::cout << "Sun altitude: " << sunTracer.calculate_sun_altitude_in_degrees(
            latitude, longitude, year, month, day, hour, minute, second
    ) << std::endl;

    std::cout << "Sun azimuth: " << sunTracer.calculate_sun_azimuth_in_degrees(
            latitude, longitude, year, month, day, hour, minute, second
    ) << std::endl;

    // Expected output:
    // Sun altitude: 36.58
    // Sun azimuth: 132.93
    //To verify the results, you can use the following website:
    //https://www.sonnenverlauf.de/#/47.0592,8.3013,10/2024.04.16/14:57/1/3


    std::cout << std::endl <<"The SunTracer class is also able to calculate the sun's altitude and azimuth from the current system time:" << std::endl;
    double sun_azimuth = sunTracer.calculate_sun_azimuth_From_Current_Systemtime_in_degrees(latitude, longitude);
    double sun_altitude = sunTracer.calculate_sun_altitude_From_Current_Systemtime_in_degrees(latitude, longitude);

    // Ausgabe der berechneten Sonnenhöhe und des Sonnenazimuts
    std::cout << "Sun altitude: " << sun_altitude << std::endl;
    std::cout << "Sun azimuth: " << sun_azimuth << std::endl;


    return 0;
}
