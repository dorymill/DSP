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

        case (TRUNC):

            // Calculate the filter kernel
            for(int n = 0; n < kernel_length; n++){
                
                //  Truncate If we're past the sample frequency 
                if((n - kernel_length/2) == 0){
                    kernel[n] = 2*PI*f_c;
                }
                
                // Sinc with no window otherwise
                if((n - kernel_length/2) != 0) {
                    kernel[n] = sin(2*PI*f_c*(n - k_len/2)) / (n - k_len/2);
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
            
            // Calculate the filter kernel
            for(int n = 0; n < kernel_length; n++){
                
                //  Truncate If we're past the sample frequency 
                if((n - kernel_length/2) == 0){
                    kernel[n] = 2*PI*f_c;
                }
                
                // Sinc part
                if((n - kernel_length/2) != 0) {
                    kernel[n] = sin(2*PI*f_c*(n - k_len/2)) / (n - k_len/2);
                    
                    // Hamming window
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
            
        case (BLACKMAN):

            // Calculate the filter kernel
            for(int n = 0; n < kernel_length; n++){
                
                //  Truncate If we're past the sample frequency 
                if((n - kernel_length/2) == 0){
                    kernel[n] = 2*PI*f_c;
                }
                
                // Sinc part
                if((n - kernel_length/2) != 0) {
                    kernel[n] = sin(2*PI*f_c*(n - k_len/2)) / (n - k_len/2);
                    
                    // Blackman window
                    kernel[n] = kernel[n] * (0.42 - 0.5*cos(2*PI*n / k_len) + 0.08*cos(4*PI*n / k_len));
                }

                // Calculate running sum for normalization
                norm += kernel[n];

            }

            // Normalize the filter at DC
            for (int n = 0; n < kernel_length; n++) {
                kernel[n] /= norm;
            }

            break;

        default:
            printf("Please select a window. Convolving with null kernel.");
            memset(kernel, 0, sizeof(kernel));
            break;
    }

    // Convolve the final output
    convolve(signal, output, kernel, sig_length - kernel_length, kernel_length);

}