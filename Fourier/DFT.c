// Exercise to calculate dft
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <String.h>

#define PI 3.14159265359

void dft(const double *signal, double *reX, double *imX, int sig_length)
{

    int i,j,k;

    for (j = 0; j < sig_length/2; j++) {
        reX[j] = 0;
        imX[j] = 0;
    }

    for(k = 0; k < sig_length / 2; k++) {
        for(i = 0; i < sig_length; i++) {
            reX[k] = reX[k] + signal[i]*cos(2*PI*k*i/sig_length);
            imX[k] = imX[k] - signal[i]*sin(2*PI*k*i/sig_length);

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


void dft_mag(const double *reX, const double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {
        output[iter] = sqrt(pow(reX[iter],2) + pow(imX[iter],2));

    }


}

void dft_phase(double *reX, double *imX, double *output, int sig_length)
{

    for(int iter = 0; iter < sig_length; iter++) {
        output[iter] = 0;

        if(reX[iter] == 0) {
            reX[iter] = pow(10,-20);
            output[iter] = atan(imX[iter]/reX[iter]);
        }

        if(reX[iter] < 0 && output[iter] < 0) { // Negative phase rollover handling 
            output[iter] = output[iter] - PI;
        }

        if(reX[iter] < 0 && output[iter] >= 0) { // Positive phase rollover handling
            output[iter] = output[iter] + PI;
        }
    }

}