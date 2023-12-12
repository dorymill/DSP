// Code to test convolution module
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Convolution.h"
#include "RunningSum.h"
#include "FirstDifference.h"

#include "../Signals/waveforms.c"
#include "../Signals/impulse_response.c"

#define SIG_LENGTH 320
#define IMP_LEN    29

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
extern double Impulse_response[IMP_LEN];
       double outputSignal[SIG_LENGTH + IMP_LEN];
       double rsumOutput[SIG_LENGTH];
       double fdOutput[SIG_LENGTH];

void main (void) {

    // Convolution Test
    //////////////////////////////////////////////////////////////////////
    FILE *pInputSig, *pResponse;

    pInputSig = fopen("../Signals/input_signal.dat", "w");
    pResponse = fopen("../Signals/impulse_response.dat", "w");

    // Write input signal to file
    for(int iter = 0; iter < SIG_LENGTH; iter++) {
        fprintf(pInputSig, "\n%f", InputSignal_f32_1kHz_15kHz[iter]);
    }

    fclose(pInputSig);

    // Write kernel to file
    for(int iter = 0; iter < IMP_LEN; iter++) {
        fprintf(pResponse, "\n%f", Impulse_response[iter]);
    }

    fclose(pResponse);

    // Convolve
    convolve(InputSignal_f32_1kHz_15kHz, 
             outputSignal, 
             Impulse_response, 
             SIG_LENGTH, 
             IMP_LEN);

    FILE *pOutput = fopen("../Signals/convolution_output.dat", "w");

    for(int iter = 0; iter < SIG_LENGTH + IMP_LEN; iter++) {
        fprintf(pOutput, "\n%f", outputSignal[iter]);
    }

    fclose(pOutput);

    // Running Sum Test
    //////////////////////////////////////////////////////////////////////
    FILE *pRSumOutFile = fopen("../Signals/running_sum_out.dat", "w");

    running_sum(InputSignal_f32_1kHz_15kHz, rsumOutput, SIG_LENGTH);

    for(int iter = 0; iter < SIG_LENGTH; iter++) {
        fprintf(pRSumOutFile, "\n%f", rsumOutput[iter]);
    }

    fclose(pRSumOutFile);

    // First Difference Test
    ///////////////////////////////////////////////////////////////////////
    FILE *pFDOutFile = fopen("../Signals/first_diff_out.dat", "w");

    first_difference(InputSignal_f32_1kHz_15kHz, fdOutput, SIG_LENGTH);

    for(int iter = 0; iter < SIG_LENGTH; iter++) {
        fprintf(pFDOutFile, "\n%f", fdOutput[iter]);
    }

    fclose(pFDOutFile);

}