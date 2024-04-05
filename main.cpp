#include <iostream>
#include "SunTracer.h"
#include <ctime>

int main() {

    // Use the SunTracer class to calculate the sun's altitude and azimuth
    // for the Location Lucerne, Switzerland on 29.03.2024 at 08:36:00 UTC
    // and print the results to the console.

    SunTracer sunTracer;
    double latitude = 47.05972;
    double longitude= 8.30906;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 9;
    int minute = 07;
    int second = 0;
    double tolerance = 0.5;

    std::cout << "Sun altitude: " << sunTracer.calculate_sun_altitue_in_degress(
            latitude, longitude, year, month, day, hour, minute, second
            ) << std::endl;

    std::cout << "Sun azimuth: " << sunTracer.calculate_sun_azimuth_in_degress(
            latitude, longitude, year, month, day, hour, minute, second
            ) << std::endl;


    // Expected output:
    // Sun altitude: 36.58
    // Sun azimuth: 132.93

    //To verify the results, you can use the following website:
    //https://www.sonnenverlauf.de/#/47.0597,8.3091,11/2024.03.29/10:07/1/3

    return 0;
}
