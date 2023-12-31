// Digital Filters Header File!
#ifndef FILTESR_H
#define FILTESR_H

typedef enum{

    TRUNC,
    HAMMING,
    BLACKMAN,

} Windows;

void lowpass(double *signal,
             double *output,
             double *kernel,
             int window,
             double cutoff,
             int sample_rate,
             int sig_length,
             int kernel_length);


#endif