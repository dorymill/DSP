// Exercise to calculate first differences
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

void first_difference(const double *signal, double *output, int sig_length) {

    for (int iter = 0; iter < sig_length; iter++) {
        
        output[iter] = signal[iter] - signal[iter-1];
    }

}