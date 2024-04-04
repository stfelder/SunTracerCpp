#include "gtest/gtest.h"
#include "SunTracer.h"
#include <ctime>
#include <iostream>





TEST(calculateSunAltitude_Test, Determine_the_height_of_the_sun) {
    SunTracer sunTracer;
    double latitude = 50.0;
    double declination = 23.44;
    double hourAngle = -30.0;
    double tolerance = 0.01;
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, declination, hourAngle), 54.63, tolerance);
}


TEST(calculateJulianDate_Test, Determine_the_Julian_date) {
    SunTracer sunTracer;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 25;
    int hour = 12;
    int minute = 0;
    int second = 0;
    EXPECT_EQ(sunTracer.getJulianDate_FROM_UTC(year, month, day, hour, minute, second), 2460395);
}


TEST(calculate_GSMT_Test, Determine_the_Greenwich_Sidereal_Mean_Time) {
    //https://www.walter-fendt.de/html5/aen/siderealtime_en.htm
    SunTracer sunTracer;
    double julianDate = 2460492.375845;
    // Erwarteter Wert für GMST basierend auf `julianDate`
    double expectedGMST = 15.64815;

    // Die Toleranz für den Vergleich
    double tolerance = 0.07; // 0.05 sind circa 3 Minuten //0.07 sind circa 4 Minuten

    // Der tatsächliche Wert von getGMST
    double actualGMST = sunTracer.getGMST(julianDate);
    EXPECT_NEAR(actualGMST, expectedGMST, tolerance);
}

TEST(calculate_LMST_Test, Determine_the_Local_Mean_Sidereal_Time) {
    //https://www.walter-fendt.de/html5/aen/siderealtime_en.htm
    SunTracer sunTracer;
    double gmst = 7.15830;
    double longitude = 47.275315; //https://www.latlong.net/
    // Erwarteter Wert für LMST basierend auf `gmst` und `longitude`
    double expectedLMST = 10.30999;

    // Die Toleranz für den Vergleich
    double tolerance = 0.01;

    // Der tatsächliche Wert von getLocalSiderealTime
    double actualLMST = sunTracer.getLocalSiderealTime(gmst, longitude);
    EXPECT_NEAR(actualLMST, expectedLMST, tolerance);
}

TEST(calculateSunDeclination_Test, Determine_the_declination_of_the_sun) {
    SunTracer sunTracer;
    double julianDate = 2460492.5;  ///01.07.2024 //182 Tag im Jahr
    // Erwarteter Wert für die Sonnendeklination basierend auf `julianDate`
    double expectedSunDeclination = 23.45; //https://polaridad.es/de/formula-declinacion-solar/

    // Die Toleranz für den Vergleich
    double tolerance = 0.5;

    // Der tatsächliche Wert von getSunDeclination_Degress
    double actualSunDeclination = sunTracer.getSunDeclination_Degress(julianDate);
    EXPECT_NEAR(actualSunDeclination, expectedSunDeclination, tolerance);
}

TEST(calculateSudRigthAscension_Test, Determine_the_right_ascension_of_the_sun) {
    SunTracer sunTracer;
    double julianDate = 2460398.812870;  ///01.07.2024 //182 Tag im Jahr
    // Erwarteter Wert für die Rektaszension der Sonne basierend auf `julianDate`
    double expectedSunRightAscension = 0.537; //https://heavens-above.com/Sun.aspx
    // Umrechnung einer Rektaszension von Stunden, Minuten und Sekunden in dezimale Stunden:
    // Dezimale RA = Stunden + (Minuten / 60) + (Sekunden / 3600)


    // Die Toleranz für den Vergleich
    double tolerance = 0.2;

    // Der tatsächliche Wert von getSunRightAscension
    double actualSunRightAscension = sunTracer.getSunRightAscension(julianDate);
    EXPECT_NEAR(actualSunRightAscension, expectedSunRightAscension, tolerance);
}

TEST(calculateHourAngle_Test, Determine_the_hour_angle) {
    SunTracer sunTracer;
    double localSiderealTime = 10.30999;
    double rightAscension = 0.0;
    // Erwarteter Wert für den Stundenwinkel basierend auf `localSiderealTime` und `rightAscension`
    double expectedHourAngle = 154.648; //Degress

    // Die Toleranz für den Vergleich
    double tolerance = 0.01;

    // Der tatsächliche Wert von getHourAngle_Degress
    double actualHourAngle = sunTracer.getHourAngle_Degress(localSiderealTime, rightAscension);
    EXPECT_NEAR(actualHourAngle, expectedHourAngle, tolerance);
}

TEST(calculateSunAltitude_Test_Determine_the_height_of_the_sun_Test, Determine_the_height_of_the_sun) {
    SunTracer sunTracer;
    double latitude = 47.20468;
    double longitude= 8.53414;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 7;
    int minute = 36;
    int second = 0;
    double tolerance = 0.2;
    // https://www.sonnenverlauf.de/#/47.2047,8.5341,8/2024.03.29/08:36/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, year, month, day, hour, minute, second), 23.56, tolerance);
}


TEST(calculateSunAzimuth_Test, Determine_the_azimuth_of_the_sun) {
    SunTracer sunTracer;
    double latitude = 47.20468;
    double longitude= 8.53414;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 7;
    int minute = 36;
    int second = 0;
    double tolerance = 0.5;
    // https://www.sonnenverlauf.de/#/47.2047,8.5341,8/2024.03.29/08:36/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 111.66, tolerance);
}


TEST(calculateSunAzimuth_Test2, Determine_the_azimuth_of_the_sun) {
    SunTracer sunTracer;
    double latitude = 46.2372;
    double longitude= 5.372;
    int year = 2024; //Time in UTC
    int month = 7;
    int day = 20;
    int hour = 6;
    int minute = 36;
    int second = 0;
    double tolerance = 0.5;
    //https://www.sonnenverlauf.de/#/46.2372,5.372,6/2024.07.20/08:36/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 84.16, tolerance);
}

TEST(calculateSunAzimuth_and_Altitude_Test, Determine_the_azimuth_and_height_of_the_sun) {
    SunTracer sunTracer;
    double latitude = 46.0714;
    double longitude= 17.9199;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 9;
    int minute = 07;
    int second = 0;
    double tolerance = 0.5;
    //https://www.sonnenverlauf.de/#/46.0714,17.9199,6/2024.03.29/10:07/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, year, month, day, hour, minute, second), 41.72, tolerance);
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 143.39, tolerance);

}


TEST(calculateSunAzimuth_and_Altitude_Test, Determine_the_azimuth_and_height_of_the_sun_South_side_Equator) {
    SunTracer sunTracer;
    double latitude = -29.1851;
    double longitude= 118.53640;
    int year = 2031; //Time in UTC
    int month = 3;
    int day = 22;
    int hour = 2;
    int minute = 07;
    int second = 0;
    double tolerance = 0.5;
    //https://www.sonnenverlauf.de/#/-29.1851,118.5364,3/2031.03.22/10:07/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, year, month, day, hour, minute, second), 47.77, tolerance);
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 50.95, tolerance);
}


TEST(calculateSunAzimuth_and_Altitude_Test, Determine_the_azimuth_and_height_of_the_sun_Eeast_side_longitude) {
    SunTracer sunTracer;
    double latitude = 36.93927;
    double longitude= -85.83455;
    int year = 2031; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 15;
    int minute = 07;
    int second = 0;
    double tolerance = 0.9;
    //https://www.sonnenverlauf.de/#/36.9393,-85.8345,6/2024.03.29/10:07/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, year, month, day, hour, minute, second), 40.41, tolerance);
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 122.20, tolerance);
}


TEST(calculateSunAzimuth_and_Altitude_Test, Determine_the_azimuth_and_height_of_the_sun_Eeast_side_longitude_and_South_side_Equator) {
    SunTracer sunTracer;
    double latitude = -23.95054;
    double longitude= -61.83349;
    int year = 2027; //Time in UTC
    int month = 8;
    int day = 20;
    int hour = 13;
    int minute = 07;
    int second = 0;
    double tolerance = 0.9;
    //https://www.sonnenverlauf.de/#/-23.9505,-61.8335,4/2027.08.20/10:07/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, year, month, day, hour, minute, second), 32.26, tolerance);
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, year, month, day, hour, minute, second), 56.08, tolerance);
}

TEST(calculateSunAzimuth_and_Altitude_Test, Determine_the_azimuth_and_height_of_the_sun_with_time_t_object){
    SunTracer sunTracer;
    double latitude = -23.95054;
    double longitude= -61.83349;


    struct tm timeinfo = {0};
    timeinfo.tm_year = 2027 - 1900; // Jahre seit 1900
    timeinfo.tm_mon = 8; // Monat, 0-basiert (0 = Januar, 7 = August)
    timeinfo.tm_mday = 20; // Tag des Monats
    timeinfo.tm_hour = 15; // Stunde (24-Stunden-Format)
    timeinfo.tm_min = 7; // Minute
    timeinfo.tm_sec = 0; // Sekunde

    // Konvertierung der tm Struktur in einen time_t Wert
    time_t localTime  = mktime(&timeinfo);

    // Umwandlung in UTC
    std::tm* gmtTime = gmtime(&localTime);
    time_t utcTime = mktime(gmtTime);

    double tolerance = 0.9;
    //https://www.sonnenverlauf.de/#/-23.9505,-61.8335,4/2027.08.20/10:07/1/3
    EXPECT_NEAR(sunTracer.calculate_sun_altitue_in_degress(latitude, longitude, utcTime), 32.26, tolerance);
    EXPECT_NEAR(sunTracer.calculate_sun_azimuth_in_degress(latitude, longitude, utcTime), 56.08, tolerance);
}