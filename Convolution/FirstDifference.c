// Exercise to calculate first differences
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

/**
 * @brief Calculates the first differences of a signal
 * 
 * @param signal     Pointer to input signal buffer
 * @param output     Pointer to output signal buffer
 * @param sig_length Signal length
 */
void first_difference(const double *signal, double *output, int sig_length) {

    for (int iter = 0; iter < sig_length; iter++) {
        
        output[iter] = signal[iter] - signal[iter-1];
    }

}