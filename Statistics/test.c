// Code to test statistics modules
#include <stdlib.h>
#include <stdio.h>
#include "Mean.h"

#include "../Signals/waveforms.c"

#define SIG_LENGTH 320

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];


void main (void) {

    double sig_mean = calc_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_LENGTH);

    printf("\nSignal Mean | %f\n", sig_mean);
    
}