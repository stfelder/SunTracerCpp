# SunTracerCpp
SunTracerCpp is a library designed to calculate the sun's position (azimuth and altitude) at a specific time and location. This library can be useful for applications in astronomy, photovoltaic planning, and many other fields where the position of the sun is relevant.
## Prerequisites
Before you start, ensure the following packages are installed on your system:
- CMake
- Git

Run the following commands to install them on a Debian-based system (like Ubuntu):

```sh
sudo apt-get update
sudo apt install cmake git
```

# Installation
## LINUX
```sh
git clone https://github.com/stfelder/SunTracerCpp.git
cd SunTracerCpp
mkdir build
cd build
cmake ..
make
./SunTracer_run

```
Now you can run the program with the following command:

```sh
./SunTracer_run
```
You should see the following output:

```sh
Sun altitude: 36.58
Sun azimuth: 132.93
```


## WINDOWS
The project has been tested with CLion on Windows.