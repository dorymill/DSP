// Exercise to calculate a signal mean
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mean.h"
#include "Variance.h"

/**
 * @brief Method to calculate the variance of a signal
 * 
 * @param signal     Pointer to input signal buffer
 * @param sig_length Signal length
 * @return double    Signal variance (Power)
 */
double calc_signal_variance (const double *signal, int sig_length) {

    double variance = 0.0;

    double mean = calc_signal_mean(signal, sig_length);

    for (int iter = 0; iter < sig_length; iter++) {
        variance += pow((signal[iter] - mean),2);
    }

    variance /= (sig_length - 1);

    return variance;
}