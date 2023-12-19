// Exercise to test filters
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Filters.h"
#include "../Convolution/Convolution.h"
#include "../Fourier/Fourier.h"

#include "../Signals/waveforms.c"

#define SIG_LEN     320
#define SIG_LEN2    501
#define ECG_LEN     640
#define KERNEL_LEN  30       // M = 4 / BW where BW is filter bandwidth relative to fs/2
#define SAMPLE_RATE 48000   // fs

extern double InputSignal_f32_1kHz_15kHz[SIG_LEN]; // 48 kHz sample rate

extern double ecg[ECG_LEN]; // 48 kHz sample rate

extern double sig_imX[SIG_LEN2]; // Unknown sample rate
extern double sig_reX[SIG_LEN2]; // Unknown sample rate

double outputSignal[SIG_LEN - KERNEL_LEN];

double sincKernel[KERNEL_LEN];
double sincReX[KERNEL_LEN/2];
double sincImX[KERNEL_LEN/2];
double sincMag[KERNEL_LEN/2];
double sincPhase[KERNEL_LEN/2];

double frequencyAxisEcg [ECG_LEN/2];
double frequencyAxisDft [SIG_LEN/2];
double frequencyAxisCdft[SIG_LEN2/2];
double frequencyAxisKernel[KERNEL_LEN/2];

double timeAxisDft      [SIG_LEN];

void main (void)
{

    // Frequency Axes
    //////////////////////////////////////////////////////////////////////
    
    FILE *pecgFreqs, *pdftFreqs, *p20HzFreqs;
    
    pecgFreqs  = fopen("../Signals/ecg_Freqs.dat",  "w");
    pdftFreqs  = fopen("../Signals/dft_Freqs.dat",  "w");
    p20HzFreqs = fopen("../Signals/20Hz_Freqs.dat", "w");

    // Populate and save Frequency Axes
    for(int iter = 0; iter < ECG_LEN / 2; iter++) {
        frequencyAxisEcg[iter] = iter*((SAMPLE_RATE/2)/(ECG_LEN/2));
        fprintf(pecgFreqs,"\n%f",frequencyAxisEcg[iter]);
    }

    for(int iter = 0; iter < SIG_LEN / 2; iter++) {
        frequencyAxisDft[iter] = iter*((SAMPLE_RATE/2)/(SIG_LEN/2));
        fprintf(pdftFreqs,"\n%f",frequencyAxisDft[iter]);
    }

    for(int iter = 0; iter < SIG_LEN2 -1; iter++) {
        frequencyAxisCdft[iter] = (double) (iter*((10000/2)/((SIG_LEN2-1)/2)))/100;
        fprintf(p20HzFreqs,"\n%f",frequencyAxisCdft[iter]);
    }

    fclose(pecgFreqs);
    fclose(pdftFreqs);
    fclose(p20HzFreqs);
    

    // Low Pass Sinc Filter Test
    //////////////////////////////////////////////////////////////////////
    FILE *pInputSig, *pOutputSig, *pKernel, *pFilterResponse, *pFilterPhase;

    // Write input signal to file
    
    pInputSig = fopen("../Signals/input_signal.dat", "w");
    
    for(int iter = 0; iter < SIG_LEN; iter++) {
        fprintf(pInputSig, "\n%f %f",iter*(1/(double) SAMPLE_RATE), InputSignal_f32_1kHz_15kHz[iter]);
    }

    fclose(pInputSig);


    // Perform the filtering
    lowpass(InputSignal_f32_1kHz_15kHz, outputSignal, sincKernel, BLACKMAN, 5000, SAMPLE_RATE, SIG_LEN, KERNEL_LEN);
    printf("\n[+] Filtering complete");


    // Write kernel to file
    pKernel = fopen("../Signals/sinc_kernel.dat", "w");

    for(int iter = 0; iter < KERNEL_LEN; iter++) {
        timeAxisDft[iter] = iter * (1 / (double) SAMPLE_RATE);
        fprintf(pKernel, "\n%f", sincKernel[iter]);
    }

    fclose(pKernel);
    printf("\n[+] Kernel written.");

    // Save the output signal
    pOutputSig = fopen("../Signals/output_filtered.dat", "w");

    for(int iter = KERNEL_LEN; iter < SIG_LEN - KERNEL_LEN; iter++) {
        timeAxisDft[iter] = iter * (1 / (double) SAMPLE_RATE);
        fprintf(pOutputSig, "\n%f %f", timeAxisDft[iter], outputSignal[iter]);
    }

    fclose(pOutputSig);
    printf("\n[+] Output signal written.");

}