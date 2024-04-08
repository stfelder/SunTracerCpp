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
    int month = 4;
    int day = 8;
    int hour = 12;
    int minute = 07;
    int second = 0;
    double tolerance = 0.5;

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
    //https://www.sonnenverlauf.de/#/47.0597,8.3091,11/2024.03.29/10:07/1/3

    // use system time to calculate the sun's altitude and azimuth
    // Hole die aktuelle Zeit als time_point
    auto now = std::chrono::system_clock::now();

    // Konvertiere time_point zu time_t, um mit der C Standardbibliothek zu arbeiten
    time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Konvertiere time_t zu tm als UTC
    std::tm* now_tm = std::gmtime(&now_c);

    // Ausgabe der UTC Zeit
    std::cout << "Aktuelle UTC Zeit: " << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << std::endl;
    //std::tm *timeInfo = std::gmtime(&now_tm);

    // Tag, monat und Jahr auslesen
    int year_now = now_tm->tm_year + 1900;
    int month_now = now_tm->tm_mon + 1;
    int day_now = now_tm->tm_mday;
    int hour_now = now_tm->tm_hour;
    int minute_now = now_tm->tm_min;
    int second_now = now_tm->tm_sec;

    // Berechnung der Sonnenhöhe und des Sonnenazimuts
    double sun_altitude = sunTracer.calculate_sun_altitude_in_degrees(
            latitude, longitude, year_now, month_now, day_now, hour_now, minute_now, second_now
    );
    double sun_azimuth = sunTracer.calculate_sun_azimuth_in_degrees(
            latitude, longitude, year_now, month_now, day_now, hour_now, minute_now, second_now
    );

    // Ausgabe der berechneten Sonnenhöhe und des Sonnenazimuts
    std::cout << "Sun altitude: " << sun_altitude << std::endl;
    std::cout << "Sun azimuth: " << sun_azimuth << std::endl;


    return 0;
}
