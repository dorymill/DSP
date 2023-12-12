// Exercise to calculate running sum
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

void running_sum(const double *signal, double *output, int sig_length) {

    for (int iter = 0; iter < sig_length; iter++) {
        
        output[iter] = signal[iter] + output[iter-1];
    }
}