// Fourier Header File
#ifndef FOURIER_H
#define FOURIER_H

void dft(const double *signal, double *reX, double *imX, int sig_length);
void cdft(double *sigRe, double *sigIm, double *reX, double *imX, int sig_length);
void inverse_dft(double *reX, double *imX, double *signal, int sig_length);
void dft_mag(double *reX, const double *imX, double *output, int sig_length);
void dft_phase(const double *reX, const double *imX, double *output, int sig_length);

#endif