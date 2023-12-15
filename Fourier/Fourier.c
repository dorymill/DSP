// Exercise to calculate dft
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

#define PI 3.14159265359

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

void dft_mag(double *reX, const double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {

        if (reX == 0) {
            reX[iter] = pow(10,-20);
        }

        output[iter] = sqrt(pow(reX[iter],2) + pow(imX[iter],2));

    }


}

void dft_phase(double *reX, double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {

        output[iter] = atan2(imX[iter],reX[iter]);

    }

}

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