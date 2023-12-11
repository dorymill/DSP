// Exercise to calculate a signal mean
#include <stdio.h>
#include <stdlib.h>
#include "Mean.h"

double calc_signal_mean (const double *signal, int sig_length) {

    double mean = 0.0;

    for (int iter = 0; iter < sig_length; iter++) {
        mean += signal[iter];
    }

    mean /= sig_length;

    return mean;
}
