// Algorithm to convert betwixt polar and rectangular coordinates
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

double * rect_to_polar(double reX, double imX) 
{
    double result[2] = {0};
    // Result[0] = r
    // Result[1] = theta

    result[0] = sqrt(pow(reX,2) + pow(imX,2));
    result[1] = atan2(imX,reX);

    if(reX == 0) {
        result[0] = pow(10,-20); // Convention
        result[1] = atan2(imX,reX);
    }

    if(reX < 0 && imX < 0) { // Handle phase overflow (technically handled by atan2)
        result[1] = result[1] - PI;
    }

    if(reX < 0 && imX >= 0) { // Handle phase underflow (technically handled by atan2)
        result[1] = result[1] + PI;
    }

    return result;
}






double * polar_to_rect(double radius, double theta)
{
    double result[2] = {0};

    result[0] = radius * cos(theta);
    result[1] = radius * sin(theta);

    return result;
}