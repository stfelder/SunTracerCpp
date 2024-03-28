//
// Created by stefanfelder on 25.03.2024.
//

#include "SunTracer.h"
template int Calculator::summe<int>(int, int);
template double Calculator::summe<double>(double, double);



template<typename T>
T Calculator::summe(T a, T b) {
    return a+b;
}
