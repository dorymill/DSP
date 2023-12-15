// Exercise to calculate signal convolution
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

/**
 * @brief Performs convolution of an input signal and kernel
 * 
 * @param signal   Pointer to input signal buffer
 * @param output   Pointer to output signal buffer
 * @param kernel   Pointer to kernel signal buffer
 * @param sig_len  Signal length
 * @param kern_len Kernel length
 */
void convolve (const double *signal, 
                     double *output,
               const double *kernel,
                        int  sig_len,
                        int  kern_len) 
{
    int i,j;

    // Set all output array elements to zero
    memset(output, 0, sizeof(output));

    // Convolve
    for(i = 0 ; i < sig_len; i++) {
        for (j = 0; j < kern_len; j++) {
            output[i+j] += signal[i]*kernel[j];
        }
    }
}