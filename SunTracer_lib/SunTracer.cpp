//
// Created by stefanfelder on 25.03.2024.
//

#include "SunTracer.h"
#include <cmath>


double SunTracer::calculate_sun_altitue_in_degress(double latitude_Degress, double declination_Degress, double hourAngle_hour) {
    // Umwandlung von Grad in Radiant
    double latitude_rad = latitude_Degress * M_PI / 180.0;
    double declination_rad = declination_Degress * M_PI / 180.0;
    hourAngle_hour = hourAngle_hour * M_PI / 180.0;

    // Berechnung der Sonnenhöhe in Radiant
    double altitude = asin(sin(latitude_rad) * sin(declination_rad) + cos(latitude_rad) * cos(declination_rad) * cos(hourAngle_hour));

    // Umwandlung der Sonnenhöhe in Grad und Rückgabe
    return altitude * 180.0 / M_PI;
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

double SunTracer::getLocalSiderealTime(double gmst, double longitude_Degress) {
    // Umrechnung des Längengrads von Grad in Stunden (360 Grad / 24 Stunden = 15 Grad pro Stunde)
    double longitudeInHours = longitude_Degress / 15.0;

    // Berechnung der Lokalen Sternenzeit
    double lst = gmst + longitudeInHours;

    // Modulieren, um sicherzustellen, dass LST im Bereich [0, 24) liegt
    lst = fmod(lst, 24.0);
    if (lst < 0) {
        lst += 24.0; // Stellen Sie sicher, dass LST positiv ist
    }

    return lst;
}


double SunTracer::getSunDeclination_Degress(double julianDate) {
    // Konvertiere Julianisches Datum in Tage seit J2000.0
    double n = julianDate - 2451545.0;

    // Mittlere Länge der Sonne (in Grad)
    double L = fmod(280.460 + 0.9856474 * n, 360.0);
    if (L < 0) L += 360.0;

    // Mittlere Anomalie der Sonne (in Grad)
    double g = fmod(357.528 + 0.9856003 * n, 360.0);
    if (g < 0) g += 360.0;

    // Ekliptikale Länge der Sonne (in Grad)
    double lambda = L + 1.915 * sin(g * M_PI / 180.0) + 0.020 * sin(2 * g * M_PI / 180.0);

    // Neigung der Ekliptik (in Grad)
    double epsilon = 23.439 - 0.0000004 * n;

    // Sonnendeklination (in Grad)
    double declination = asin(sin(epsilon * M_PI / 180.0) * sin(lambda * M_PI / 180.0)) * 180.0 / M_PI;

    return declination;
}


double SunTracer::getHourAngle_Degress(double localSiderealTime, double rightAscension) {
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

double SunTracer::getSunTrueLongitude(double julianDate) {
    double n = julianDate - 2451545.0; // Tage seit dem Referenzdatum J2000.0
    double L = fmod(280.460 + 0.9856474 * n, 360.0); // Mittlere Länge der Sonne
    double g = fmod(357.528 + 0.9856003 * n, 360.0); // Mittlere Anomalie
    double lambda = L + 1.915 * sin(g * degToRad) + 0.020 * sin(2 * g * degToRad); // Wahre Länge
    return lambda;
}

double SunTracer::getSunRightAscension(double julianDate) {
    double epsilon = 23.439 - 0.0000004 * (julianDate - 2451545.0); // Schiefe der Ekliptik
    double lambda = getSunTrueLongitude(julianDate); // Wahre Länge der Sonne

    // Umwandlung in äquatoriale Koordinaten
    double RA = atan2(cos(epsilon * degToRad) * sin(lambda * degToRad), cos(lambda * degToRad)) / degToRad;
    RA = fmod(RA, 360.0);
    if (RA < 0) RA += 360.0;

    // Umwandlung von Grad in Stunden
    RA /= 15.0;

    return RA;
}

double SunTracer::calculate_sun_altitue_in_degress(double latitude_Degress, double longitude_Degress, int year, int month, int day, int hour_UTC, int minute, int second) {
    double julianDate = getJulianDate_FROM_UTC(year, month, day, hour_UTC, minute, second);
    double declination = getSunDeclination_Degress(julianDate);
    double hourAngle = getHourAngle_Degress(getLocalSiderealTime(getGMST(julianDate), longitude_Degress),
                                            getSunRightAscension(julianDate));
    return calculate_sun_altitue_in_degress(latitude_Degress, declination, hourAngle);
}


double SunTracer::calculate_sun_azimuth_in_degress(double latitude_Degrees, double declination_Degrees, double hourAngle_Degrees) {
    // Umwandlung der Eingabewerte von Grad in Radian
    double latitude_Radians = latitude_Degrees * M_PI / 180.0;
    double declination_Radians = declination_Degrees * M_PI / 180.0;
    double hourAngle_Radians = hourAngle_Degrees * M_PI / 180.0;

    // Berechnung des Azimuts in Radian

    double azimuth_Radians = atan2(sin(hourAngle_Radians),
                                   cos(hourAngle_Radians) * sin(latitude_Radians) -
                                   tan(declination_Radians) * cos(latitude_Radians));

    // Umwandlung des Azimuts von Radian in Grad
    double azimuth_Degrees = azimuth_Radians * 180.0 / M_PI;

    // Stellen Sie sicher, dass der Azimut im Bereich von 0° bis 360° liegt
    if (azimuth_Degrees < 0) {
        azimuth_Degrees += 360.0;
    }

    return azimuth_Degrees -180;
}


double SunTracer::calculate_sun_azimuth_in_degress(double latitude_Degress, double longitude_Degress, int year, int month, int day,
                                                   int hour_UTC, int minute, int second) {
    double julianDate = getJulianDate_FROM_UTC(year, month, day, hour_UTC, minute, second);
    double declination = getSunDeclination_Degress(julianDate);
    double hourAngle = getHourAngle_Degress(getLocalSiderealTime(getGMST(julianDate), longitude_Degress),
                                            getSunRightAscension(julianDate));
    return calculate_sun_azimuth_in_degress(latitude_Degress, declination, hourAngle);

}

double SunTracer::calculate_sun_altitue_in_degress(double latitude, double longitude, std::time_t time_UTC) {
    int yearOffSet = 1900;
    std::tm *timeInfo = std::gmtime(&time_UTC);
    auto temp = calculate_sun_altitue_in_degress(latitude, longitude,
                                                 timeInfo->tm_year + yearOffSet, timeInfo->tm_mon, timeInfo->tm_mday,
                                                 timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    return temp;
}

double SunTracer::calculate_sun_azimuth_in_degress(double latitude, double declination, std::time_t time_UTC) {
    int yearOffSet = 1900;
    std::tm *timeInfo = std::gmtime(&time_UTC);
    auto temp = calculate_sun_azimuth_in_degress(latitude, declination,
                                                 timeInfo->tm_year + yearOffSet, timeInfo->tm_mon, timeInfo->tm_mday,
                                                 timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    return temp;
}


