// Exercise to calculate dft
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

#define PI 3.14159265359

/**
 * @brief Calculates the real DFT of a real valued signal.
 * 
 * @param signal     Pointer to input signal buffer
 * @param reX        Pointer to output real sample buffer
 * @param imX        Pointer to output imaginary sample buffer
 * @param sig_length Signal length
 */
void dft(const double *signal, double *reX, double *imX, int sig_length)
{

    int i,j,k;

    double norm = (double) 2 / (double) sig_length;

    for (j = 0; j < sig_length/2; j++) {
        reX[j] = 0;
        imX[j] = 0;
    }

    for(k = 0; k < sig_length / 2; k++) {
        for(i = 0; i < sig_length; i++) {
            reX[k] += norm*(signal[i]*cos(2*PI*k*i/sig_length));
            imX[k] += norm*(-signal[i]*sin(2*PI*k*i/sig_length));

        }
    }
}

/**
 * @brief Calculates the inverse DFT given input real and imaginary samples.
 * 
 * @param reX        Pointer to real valued input sample buffer
 * @param imX        Pointer to imaginary valued input sample buffer
 * @param signal     Pointer to output signal buffer
 * @param dft_length Fourier transform length
 */
void inverse_dft(double *reX, double *imX, double *signal, int dft_length)
{

    int i,j,k;

    for (j = 0; j < dft_length; j++) {
        signal[j] = 0;
    }

    for(k = 0; k < dft_length/2; k++) {

        reX[k] =  reX[k]/(dft_length/2);
        imX[k] = -imX[k]/(dft_length/2);

    }

    reX[0] =  reX[0]/2;
    imX[0] = -imX[0]/2;

    for (k = 0; k <dft_length/2; k++) {
        for (i = 0; i < dft_length; i++) {

            signal[i] = signal[i] + reX[k]*cos(2*PI*k*i/dft_length);
            signal[i] = signal[i] + imX[k]*sin(2*PI*k*i/dft_length);
        }
    }


}

/**
 * @brief Calculates the magnitude of a discrete fourier transform point
 * 
 * @param reX        Pointer to real valued input sample buffer
 * @param imX        Pointer to imaginary valued input sample buffer
 * @param output     Pointer to output magnitude buffer
 * @param sig_length Signal length
 */
void dft_mag(double *reX, const double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {

        if (reX == 0) {
            reX[iter] = pow(10,-20);
        }

        output[iter] = sqrt(pow(reX[iter],2) + pow(imX[iter],2));

    }


}

/**
 * @brief Calculates the phase of a discrete fourier transform point
 * 
 * @param reX        Pointer to real valued input sample buffer
 * @param imX        Pointer to imaginary valued input sample buffer
 * @param output     Pointer to output phase buffer
 * @param sig_length Signal length
 */
void dft_phase(double *reX, double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {

        output[iter] = atan2(imX[iter],reX[iter]);

    }

}

/**
 * @brief Calculates the complex DFT using a complex valued input signal.
 * 
 * @param sigRe      Pointer to real valued input buffer
 * @param sigIm      Pointer to complex valued input buffer
 * @param reX        Pointer to real valued output buffer
 * @param imX        Pointer to complex valued output buffer
 * @param sig_length Signal length
 */
void cdft(double *sigRe, double *sigIm, double *reX, double *imX, int sig_length)
{

    double real, imag, norm;

    norm = (double) 1 / (double) sig_length;

    for(int k = 0; k < sig_length-1;k++){
        for(int i = 0; i < sig_length-1; i++) {

            real =  cos(2*PI*k*i/sig_length);
            imag = -sin(2*PI*k*i/sig_length);

            reX[k] += norm*(sigRe[i]*real - sigIm[i]*imag);
            imX[k] += norm*(sigRe[i]*imag + sigIm[i]*real); 
        }
    }
}