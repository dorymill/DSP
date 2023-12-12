// Convolution Calculation Header File
#ifndef CONVOLUTION_H
#define CONVOLUTION_H

void convolve (const double *signal, 
                     double *output,
               const double *response,
                        int  sig_len,
                        int  resp_len);

#endif