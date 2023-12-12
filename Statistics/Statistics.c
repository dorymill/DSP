// Code to test statistics modules
#include <stdlib.h>
#include <stdio.h>
#include "Mean.h"
#include "Variance.h"
#include "StdDeviation.h"

#include "../Signals/waveforms.c"
#include "../Signals/impulse_response.c"

#define SIG_LENGTH 320
#define IMP_LEN    29

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
extern double  Impulse_response[IMP_LEN];


void main (void) {

    double sig_mean     = calc_signal_mean     (InputSignal_f32_1kHz_15kHz, SIG_LENGTH);
    double sig_variance = calc_signal_variance (InputSignal_f32_1kHz_15kHz, SIG_LENGTH);
    double sig_stddev   = calc_signal_deviation(InputSignal_f32_1kHz_15kHz, SIG_LENGTH);

    printf("\nSignal Mean | %f\n", sig_mean);
    printf("Signal Variance | %f\n", sig_variance);
    printf("Signal Std. Devation | %f\n\n", sig_stddev);
    
}