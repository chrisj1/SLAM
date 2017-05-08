//
// Created by Chris Jerrett on 4/23/17.
//

#include "../include/Calculations.h"

inline double to_radians(double degrees) {
    return degrees / 180.0 * M_PI;
}

inline double to_degrees(double radians) {
        return radians * (180.0 / M_PI);
}

inline int max(int a, int b) {
    return a>b?a:b;
}

inline int min(int a, int b) {
    return a<b?a:b;
}