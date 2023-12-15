// Exercise to calculate a signal standard deviation
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mean.h"
#include "Variance.h"

/**
 * @brief Calculates the population standard deviation of a signal
 * 
 * @param signal     Pointer to input signal buffer
 * @param sig_length Signal length
 * @return double    Signal standard deviation
 */
double calc_signal_deviation (const double *signal, int sig_length) {

    double variance = calc_signal_variance (signal, sig_length);

    double std_deviation = sqrt(variance);

    return std_deviation;
}