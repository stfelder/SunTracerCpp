project(Calculator)

set(HEADER_FILES
        SunTracer.h
        Shade_Sun_Exposure_Checker.cpp
        Shade_Sun_Exposure_Checker.h
)

set(SOURCE_FILES
        SunTracer.cpp
        Shade_Sun_Exposure_Checker.cpp
        Shade_Sun_Exposure_Checker.h
)

add_library(SunTracer_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})