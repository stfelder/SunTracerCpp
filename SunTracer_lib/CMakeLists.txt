project(Calculator)

set(HEADER_FILES
        SunTracer.h
)

set(SOURCE_FILES
        SunTracer.cpp
)

add_library(SunTracer_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})