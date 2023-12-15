// Exercise to calculate Fourier Transforms
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Fourier.h"

#include "../Signals/waveforms.c"

#define SIG_LEN     320
#define SIG_LEN2    501
#define ECG_LEN     640
#define SAMPLE_RATE 48000

extern double InputSignal_f32_1kHz_15kHz[SIG_LEN]; // 48 kHz sample rate

extern double ecg[ECG_LEN]; // 48 kHz sample rate

extern double sig_imX[SIG_LEN2]; // Unknown sample rate
extern double sig_reX[SIG_LEN2]; // Unknown sample rate

       double outputReX      [SIG_LEN/2];
       double outputImX      [SIG_LEN/2];
       double outputMag      [SIG_LEN/2];
       double recreatedSignal[SIG_LEN];

       double ecgReX  [ECG_LEN/2];
       double ecgImX  [ECG_LEN/2];
       double ecgRec  [ECG_LEN];
       double ecgMag  [ECG_LEN/2];
       double ecgPhase[ECG_LEN/2];

       double _20HzCDFTreX  [SIG_LEN2-1];
       double _20HzCDFTimX  [SIG_LEN2-1];
       double _20HzCDFTMag  [SIG_LEN2-1];
       double _20HzCDFTPhase[SIG_LEN2-1];

       double frequencyAxisEcg [ECG_LEN/2];
       double frequencyAxisDft [SIG_LEN/2];
       double frequencyAxisCdft[SIG_LEN2-1];

void main (void) {

    FILE *pReOutFile, *pImOutFile, *pMagOutFile, *pRecFile;
    FILE *pecgFreqs, *pdftFreqs, *p20HzFreqs;

    // Frequency Axis
    ///////////////////////////////////////////////////////////////////
    {
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
    }

    // DFT Example
    ////////////////////////////////////////////////////////////////////////////////
    {
    pReOutFile  = fopen("../Signals/dft_reX.dat", "w");
    pImOutFile  = fopen("../Signals/dft_imX.dat", "w");
    pMagOutFile = fopen("../Signals/dft_mag.dat", "w");

    // Do the magic
    dft(InputSignal_f32_1kHz_15kHz, outputReX, outputImX, SIG_LEN);
    dft_mag(outputReX, outputImX, outputMag, SIG_LEN/2);

    //Write the outputs
    for (int iter = 0; iter < SIG_LEN /2; iter++) {
        fprintf(pReOutFile,  "\n%f %f",frequencyAxisDft[iter], outputReX[iter]);
        fprintf(pImOutFile,  "\n%f %f",frequencyAxisDft[iter], outputImX[iter]);
        fprintf(pMagOutFile, "\n%f %f",frequencyAxisDft[iter], outputMag[iter]);
    }

    fclose(pReOutFile);
    fclose(pImOutFile);
    fclose(pMagOutFile);
    }

    // IDFT Example
    ///////////////////////////////////////////////////////////////////////////////////
    {
    pRecFile = fopen("../Signals/idft_signal.dat", "w");

    inverse_dft(outputReX, outputImX, recreatedSignal, SIG_LEN);

    for (int iter = 0; iter < SIG_LEN; iter++) {
        fprintf(pRecFile, "\n%f", recreatedSignal[iter]);
    }

    fclose(pRecFile);
    }

    // ECG Example
    ///////////////////////////////////////////////////////////////////////////////////
    {
    FILE *pECG, *pReECG, *pImECG, *precECG, *pecgMag, *pecgPhase;

    // Write the initial ECG.dat
    pECG = fopen("../Signals/ECG.dat", "w");

    for(int iter = 0; iter < ECG_LEN; iter++) {
        fprintf(pECG, "\n%f", ecg[iter]);
    }

    fclose(pECG);

    // DFT the ECG and save the result
    dft(ecg, ecgReX, ecgImX, ECG_LEN);

    dft_mag(ecgReX, ecgImX, ecgMag, ECG_LEN/2);
    dft_phase(ecgReX, ecgImX, ecgPhase, ECG_LEN/2);

    // Now do the inverse
    inverse_dft(ecgReX, ecgImX, ecgRec, ECG_LEN);

    //Write the outputs
    pReECG    = fopen("../Signals/ecg_reX.dat",   "w");
    pImECG    = fopen("../Signals/ecg_imX.dat",   "w");
    pecgMag   = fopen("../Signals/ecg_mag.dat",   "w");
    pecgPhase = fopen("../Signals/ecg_phase.dat", "w");

    for (int iter = 0; iter < ECG_LEN /2; iter++) {
        fprintf(pReECG,    "\n%f %f",frequencyAxisEcg[iter], ecgReX[iter]);
        fprintf(pImECG,    "\n%f %f",frequencyAxisEcg[iter], ecgImX[iter]);
        fprintf(pecgMag,   "\n%f %f",frequencyAxisEcg[iter], ecgMag[iter]);
        fprintf(pecgPhase, "\n%f %f",frequencyAxisEcg[iter], ecgPhase[iter]);
    }

    fclose(pReECG);
    fclose(pImECG);
    fclose(pecgMag);
    fclose(pecgPhase);

    precECG = fopen("../Signals/ecg_idft_signal.dat", "w");

    for (int iter = 0; iter < ECG_LEN; iter++) {
        fprintf(precECG, "\n%f", ecgRec[iter]);
    }

    fclose(precECG);
    }

    // Complex DFT Example
    //////////////////////////////////////////////////////////////////////
    {
    FILE *p20HzReFile, *p20HzImFile, *p20HzReCDFTFile, *p20HzImCDTFile, *p20HzMagFile, *p20HzPhaseFile;

    // Write the signal files
    p20HzReFile = fopen("../Signals/20Hz_Real_Signal.dat",    "w");
    p20HzImFile = fopen("../Signals/20Hz_Complex_Signal.dat", "w");

    for(int iter = 0; iter < SIG_LEN2; iter++) {
        fprintf(p20HzReFile, "\n%f", sig_reX[iter]);
        fprintf(p20HzImFile, "\n%f", sig_imX[iter]);
    }

    fclose(p20HzReFile);
    fclose(p20HzImFile);

    // Do the Magic
    cdft(sig_reX, sig_imX, _20HzCDFTreX, _20HzCDFTimX, SIG_LEN2);
    dft_mag(_20HzCDFTreX, _20HzCDFTimX, _20HzCDFTMag, SIG_LEN2-1);
    dft_phase(_20HzCDFTreX, _20HzCDFTimX, _20HzCDFTPhase, SIG_LEN2-1);

    //Write the outputs
    p20HzReCDFTFile = fopen("../Signals/20Hz_reX.dat",   "w");
    p20HzImCDTFile  = fopen("../Signals/20Hz_imX.dat",   "w");
    p20HzMagFile    = fopen("../Signals/20Hz_mag.dat",   "w");
    p20HzPhaseFile  = fopen("../Signals/20Hz_phase.dat", "w");

    for (int iter = 0; iter < SIG_LEN2 - 1; iter++) {
        fprintf(p20HzReCDFTFile, "\n%f %f",frequencyAxisCdft[iter], _20HzCDFTreX[iter]);
        fprintf(p20HzImCDTFile,  "\n%f %f",frequencyAxisCdft[iter], _20HzCDFTimX[iter]);
        fprintf(p20HzMagFile,    "\n%f %f",frequencyAxisCdft[iter], _20HzCDFTMag[iter]);
        fprintf(p20HzPhaseFile,  "\n%f %f",frequencyAxisCdft[iter], _20HzCDFTPhase[iter]);
    }

    fclose(p20HzReCDFTFile);
    fclose(p20HzImCDTFile);
    fclose(p20HzMagFile);
    fclose(p20HzPhaseFile);
    }

}