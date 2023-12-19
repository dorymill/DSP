// Digital Filters!
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>
#include "Filters.h"
#include "../Convolution/Convolution.h"

#define PI 3.14159265358979323846

/**
 * @brief Perform low pass filtering on an input signal
 * 
 * @param signal         Pointer to input signal buffer
 * @param output         Pointer to output signal buffer
 * @param kernel         Pointer to kernel signal buffer
 * @param window         Window function
 * @param cutoff         Cutoff frequency (Hz)
 * @param sample_rate    Sample rate
 * @param sig_length     Signal length
 * @param kernel_length  Kernel length
 */
void lowpass(double *signal,
             double *output,
             double *kernel,
             int window,
             double cutoff,
             int sample_rate,
             int sig_length,
             int kernel_length)
{

    // Calculate cutoff frequency relative to sample rate
    double f_c  = (cutoff/((double) sample_rate/2));
    double k_len = (double) kernel_length;
    double norm  = 0;

    // Calculate filter based on window
    switch (window) {

        case (SINC):
            
            // Calculate the filter kernel
            for(int n = 0; n < kernel_length; n++){
                
                // If we're past the sample frequency 
                if((n - kernel_length/2) == 0){
                    kernel[n] = 2*PI*f_c;
                }
                
                if((n - kernel_length/2) != 0) {
                    kernel[n] = sin(2*PI*f_c*(n - k_len/2)) / (n - k_len/2);
                    // Window this sucker
                    kernel[n] = kernel[n] * (0.54 - 0.46*cos(2*PI*n / k_len));
                }

                // Calculate running sum for normalization
                norm += kernel[n];

            }

            // Normalize the filter at DC
            for (int n = 0; n < kernel_length; n++) {
                kernel[n] /= norm;
            }

            break;
            

        case (HAMMING):
            break;

        case (BLACKMON):
            break;
    }

    //Now convolve the filter kernel with the signal to produce the output
    // for(int i = kernel_length; i < sig_length - kernel_length; i++) {
    //     for (int j = 0; j < kernel_length; j++) {
    //         output[i] += signal[i-j]*kernel[j];
    //     }
    // }

    convolve(signal, output, kernel, sig_length - kernel_length, kernel_length);

}