/*
 * libsonofy - signalprocessing
 * sonofy_FFT.h
 *
 * Discrete Fourier Transform algorithms
 * 2016, Alessio Degani <alessio.degani@gmail.com>
 *
 */

#ifndef LIBSONOFY_FFT_H
#define LIBSONOFY_FFT_H

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {RECT, HANN, GAUSS} sonofy_WNDtype;

typedef struct {
	uint16_t 	NFFT;
	uint16_t 	NBUFFER;
	float 		*twiddleRe, *twiddleIm;
    	float		*fftABS;
    	float		*fftAngle;
	float		*WND;
    	sonofy_WNDtype 	WNDType;
	bool 		twiddleReady;
    	bool  		wndReady;

} sonofy_FFTParams;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t sonofy_initFFT     ( sonofy_FFTParams *fft, uint16_t NFFT, uint16_t NBUFFER, sonofy_WNDtype WNDType );
uint32_t sonofy_FFTReal     ( float *signalData, sonofy_FFTParams *fft );
uint32_t sonofy_FFTComplex  ( float *IQData, sonofy_FFTParams *fft );

#ifdef __cplusplus
}
#endif

#endif // LIBSONOFY_FFT_H
