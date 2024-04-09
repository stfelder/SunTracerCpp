//
// Created by stefanfelder on 23.03.2024.
//

#include "SunTracer.h"
#include <cmath>


double SunTracer::calculate_sun_altitude_in_degrees(double latitude_Degrees, double declination_Degrees, double hourAngle_hour) {
    // Umwandlung von Grad in Radiant
    double latitude_rad = latitude_Degrees * degToRad;
    double declination_rad = declination_Degrees * degToRad;
    hourAngle_hour = hourAngle_hour * degToRad;

    // Berechnung der Sonnenhöhe in Radiant
    double altitude = asin(sin(latitude_rad) * sin(declination_rad) + cos(latitude_rad) * cos(declination_rad) * cos(hourAngle_hour));

    // Umwandlung der Sonnenhöhe in Grad und Rückgabe
    return altitude * radToDeg;
}

double SunTracer::getJulianDate_FROM_UTC(int year, int month, int day, int hour_UTC, int minute, int second) {
    // Die Monate Januar und Februar werden als 13. und 14. Monat des vorherigen Jahres betrachtet
    if (month <= 2) {
        year -= 1;
        month += 12;
    }

    // Berechnung der Hilfswerte A und B
    int A = year / 100;
    int B = 2 - A + A / 4;

    // Umrechnung der Uhrzeit in einen Bruchteil eines Tages
    double hourFraction = (hour_UTC + minute / 60.0 + second / 3600.0) / 24.0;

    // Julianisches Datum
    double JD = floor(365.25 * (year + 4716)) + floor(30.6001 * (month + 1)) + day + hourFraction + B - 1524.5;

    return JD;
}

double SunTracer::getGMST(double julianDate) {
    // Umwandlung des Julianischen Datums zum Julianischen Jahrhundert
    double T = (julianDate - 2451545.0) / 36525.0;

    // GMST in Stunden bei 0h UT
    double GMST = 6.697374558 + 2400.051336 * T + 0.000025862 * T * T;
    GMST = fmod(GMST, 24.0); // Modulo 24, um den Wert in den Bereich [0, 24) zu bringen

    // Umrechnung des Tagesbruchteils in Stunden
    double UT = fmod(julianDate + 0.5, 1.0) * 24.0;
    double GMST_hours = GMST + UT * 1.002737909;

    // Sicherstellen, dass das Ergebnis im Bereich [0, 24) Stunden bleibt
    GMST_hours = fmod(GMST_hours, 24.0);
    if (GMST_hours < 0) {
        GMST_hours += 24.0;
    }

    return GMST_hours;
}

double SunTracer::getLocalSiderealTime(double gmst, double longitude_Degrees) {
    // Umrechnung des Längengrads von Grad in Stunden (360 Grad / 24 Stunden = 15 Grad pro Stunde)
    double longitudeInHours = longitude_Degrees / 15.0;

    // Berechnung der Lokalen Sternenzeit
    double lst = gmst + longitudeInHours;

    // Modulieren, um sicherzustellen, dass LST im Bereich [0, 24) liegt
    lst = fmod(lst, 24.0);
    if (lst < 0) {
        lst += 24.0; // Stellen Sie sicher, dass LST positiv ist
    }

    return lst;
}


double SunTracer::getSunDeclination_Degrees(double julianDate) {
    // Konvertiere Julianisches Datum in Tage seit J2000.0
    double n = julianDate - J2000;

    // Mittlere Länge der Sonne (in Grad)
    double L = fmod(280.460 + 0.9856474 * n, 360.0);
    if (L < 0) L += 360.0;

    // Mittlere Anomalie der Sonne (in Grad)
    double g = fmod(357.528 + 0.9856003 * n, 360.0);
    if (g < 0) g += 360.0;

    // Ekliptikale Länge der Sonne (in Grad)
    double lambda = L + 1.915 * sin(g * degToRad) + 0.020 * sin(2 * g * degToRad);

    // Neigung der Ekliptik (in Grad)
    double epsilon = 23.439 - 0.0000004 * n;

    // Sonnendeklination (in Grad)
    double declination = asin(sin(epsilon * degToRad) * sin(lambda * degToRad)) * radToDeg;

    return declination;
}


double SunTracer::getHourAngle_Degrees(double localSiderealTime, double rightAscension) {
    // Berechnung des Stundenwinkels in Stunden
    double hourAngle = localSiderealTime - rightAscension;

    // Normalisierung des Stundenwinkels in den Bereich [0, 24) Stunden
    hourAngle = fmod(hourAngle, 24.0);
    if (hourAngle < 0) {
        hourAngle += 24.0; // Stellen Sie sicher, dass der Stundenwinkel positiv ist
    }
    double hourAngle_Degress= hourAngle * 15.0;
    return hourAngle_Degress;
}

double SunTracer::getSunTrueLongitude(double julianDate) const {
    double n = julianDate - J2000; // Tage seit dem Referenzdatum J2000.0
    double L = fmod(280.460 + 0.9856474 * n, 360.0); // Mittlere Länge der Sonne
    double g = fmod(357.528 + 0.9856003 * n, 360.0); // Mittlere Anomalie
    double lambda = L + 1.915 * sin(g * degToRad) + 0.020 * sin(2 * g * degToRad); // Wahre Länge
    return lambda;
}

double SunTracer::getSunRightAscension(double julianDate) {
    double epsilon = 23.439 - 0.0000004 * (julianDate - J2000); // Schiefe der Ekliptik
    double lambda = getSunTrueLongitude(julianDate); // Wahre Länge der Sonne

    // Umwandlung in äquatoriale Koordinaten
    double RA = atan2(cos(epsilon * degToRad) * sin(lambda * degToRad), cos(lambda * degToRad)) / degToRad;
    RA = fmod(RA, 360.0);
    if (RA < 0) RA += 360.0;

    // Umwandlung von Grad in Stunden
    RA /= 15.0;

    return RA;
}

double SunTracer::calculate_sun_altitude_in_degrees(double latitude_Degrees, double longitude_Degrees, int year, int month, int day, int hour_UTC, int minute, int second) {
    double julianDate = getJulianDate_FROM_UTC(year, month, day, hour_UTC, minute, second);
    double declination = getSunDeclination_Degrees(julianDate);
    double hourAngle = getHourAngle_Degrees(getLocalSiderealTime(getGMST(julianDate), longitude_Degrees),
                                            getSunRightAscension(julianDate));
    return calculate_sun_altitude_in_degrees(latitude_Degrees, declination, hourAngle);
}


double SunTracer::calculate_sun_azimuth_in_degrees(double latitude_Degrees, double declination_Degrees, double hourAngle_Degrees) {
    // Umwandlung der Eingabewerte von Grad in Radian
    double latitude_Radians = latitude_Degrees * degToRad;
    double declination_Radians = declination_Degrees * degToRad;
    double hourAngle_Radians = hourAngle_Degrees * degToRad;

    // Berechnung des Azimuth in Radian

    double azimuth_Radians = atan2(sin(hourAngle_Radians),
                                   cos(hourAngle_Radians) * sin(latitude_Radians) -
                                   tan(declination_Radians) * cos(latitude_Radians));

    // Umwandlung des Azimuth von Radian in Grad
    double azimuth_Degrees = azimuth_Radians * radToDeg;

    azimuth_Degrees += 180.0; // Umrechnung von Nord nach Süd Todo: Check if this is correct

    // Stellen Sie sicher, dass der Azimut im Bereich von 0° bis 360° liegt
    if (azimuth_Degrees > 360) {
        azimuth_Degrees -= 360.0;
    }

    return azimuth_Degrees;
}


double SunTracer::calculate_sun_azimuth_in_degrees(double latitude_Degrees, double longitude_Degrees, int year, int month, int day,
                                                   int hour_UTC, int minute, int second) {
    double julianDate = getJulianDate_FROM_UTC(year, month, day, hour_UTC, minute, second);
    double declination = getSunDeclination_Degrees(julianDate);
    double hourAngle = getHourAngle_Degrees(getLocalSiderealTime(getGMST(julianDate), longitude_Degrees),
                                            getSunRightAscension(julianDate));
    return calculate_sun_azimuth_in_degrees(latitude_Degrees, declination, hourAngle);

}

double SunTracer::calculate_sun_altitude_in_degrees(double latitude, double declination, std::time_t time_UTC) {
    int yearOffSet = 1900;
    std::tm *timeInfo = std::gmtime(&time_UTC);
    auto temp = calculate_sun_altitude_in_degrees(latitude, declination,
                                                  timeInfo->tm_year + yearOffSet, timeInfo->tm_mon, timeInfo->tm_mday,
                                                  timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    return temp;
}

double SunTracer::calculate_sun_azimuth_in_degrees(double latitude, double declination, std::time_t time_UTC) {
    int yearOffSet = 1900;
    std::tm *timeInfo = std::gmtime(&time_UTC);
    auto temp = calculate_sun_azimuth_in_degrees(latitude, declination,
                                                 timeInfo->tm_year + yearOffSet, timeInfo->tm_mon, timeInfo->tm_mday,
                                                 timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    return temp;
}

double
SunTracer::calculate_sun_azimuth_From_Current_Systemtime_in_degrees(double latitude_Degrees, double longitude_Degrees) {
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

    return calculate_sun_azimuth_in_degrees(latitude_Degrees, longitude_Degrees, year_now, month_now, day_now, hour_now, minute_now, second_now);
}


double
SunTracer::calculate_sun_altitude_From_Current_Systemtime_in_degrees(double latitude_Degrees, double longitude_Degrees) {
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

    return calculate_sun_altitude_in_degrees(latitude_Degrees, longitude_Degrees, year_now, month_now, day_now, hour_now, minute_now, second_now);
}


