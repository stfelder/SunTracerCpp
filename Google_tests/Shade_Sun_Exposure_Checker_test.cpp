//
// Created by stefanfelder on 16.04.2024.
//
#include "gtest/gtest.h"
#include "Shade_Sun_Exposure_Checker.h"

TEST(test_is_sun_shining_on_shade, Sun_is_shining_on_shade) {

    double shaden_azimuth = 180.0;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 7;
    int minute = 36;
    int second = 0;
    double latitude = 47.2745;
    double longitude = 8.4629;
    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    //http://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/08:36/1/3
    EXPECT_TRUE(shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day, hour, minute, second, latitude, longitude));
}


TEST(test_is_sun_shining_on_shade, Sun_is_not_shining_on_shade) {
    double shaden_azimuth = 90.0;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 11;
    int minute = 50;
    int second = 0;
    double latitude = 47.2745;
    double longitude = 8.4629;
    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    //https://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/08:36/1/3
    EXPECT_FALSE(shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day, hour, minute, second, latitude, longitude));
}


TEST(test_is_sun_shining_on_shade, It_is_night){
    double shaden_azimuth = 90.0;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 4;
    int minute = 0;
    int second = 0;
    double latitude = 47.2745;
    double longitude = 8.4629;
    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    //https://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/08:36/1/3
    EXPECT_FALSE(shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day, hour,
                                                                 minute, second, latitude, longitude));
}


TEST(test_is_sun_shining_on_shade, Sun_is_in_start_tolerance){
    double shaden_azimuth = 180.0;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 8;
    int minute = 36;
    int second = 0;
    double latitude = 47.2745;
    double longitude = 8.4629;
    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    double shaden_Direction_tolerance_start_in_degrees = 45.0;
    //http://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/07:36/1/3
    EXPECT_FALSE(shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day, hour,
                                                                 minute, second, latitude, longitude,
                                                                 shaden_Direction_tolerance_start_in_degrees));
}

TEST(test_is_sun_shining_on_shade, Sun_is_in_end_tolerance){
    double shaden_azimuth = 180.0;
    int year = 2024; //Time in UTC
    int month = 3;
    int day = 29;
    int hour = 14;
    int minute = 36;
    int second = 0;
    double latitude = 47.2745;
    double longitude = 8.4629;
    double shaden_Direction_tolerance_end_in_degrees = 45.0;
    Shade_Sun_Exposure_Checker shadeSunExposureChecker(longitude,latitude);
    //http://www.sonnenverlauf.de/#/47.2745,8.4629,8/2024.03.29/13:36/1/3
    EXPECT_FALSE(shadeSunExposureChecker.is_sun_shining_on_shade(shaden_azimuth, year, month, day,
                                                                 hour, minute, second, latitude,
                                                                 longitude,5.0,
                                                                 shaden_Direction_tolerance_end_in_degrees));
}






























