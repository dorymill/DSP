// Exercise to calculate signal convolution
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

void convolve (const double *signal, 
                     double *output,
               const double *response,
                        int  sig_len,
                        int  resp_len) 
{
    int i,j;

    // Set all output array elements to zero
    memset(output, 0, sizeof(output));

    // Convolve
    for(i = 0 ; i < sig_len; i++) {
        for (j = 0; j < resp_len; j++) {
            output[i+j] += signal[i]*response[j];
        }
    }
}