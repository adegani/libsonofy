/*
 * libsonofy - signalprocessing
 * sonofy_FFT.c
 *
 * Discrete Fourier Transform algorithms
 * 2016, Alessio Degani <alessio.degani@gmail.com>
 *
 */

#include "sonofy_FFT.h"

uint32_t calcTwiddle ( sonofy_FFTParams *fft ){
    // Generate TWIDDLE factor for FFT
    float Arg;
    int32_t j;

    for( j=0; j<fft->NFFT; j++ ){
        Arg = 2 * M_PI * (float)j / (float)fft->NFFT;
        fft->twiddleRe[j] = cos(Arg);
        fft->twiddleIm[j] = -sin(Arg);
    }
    fft->twiddleReady = 1;
    return 0;
}

uint32_t GenRectWin    ( sonofy_FFTParams *fft ){
    // Generate RECTANGULAR window
    int32_t n;
    for ( n=0; n < fft->NBUFFER; n++){
        fft->WND[n] = 1;
    }
    fft->wndReady = 1;
    return 0;
}

uint32_t GenGaussWin   ( sonofy_FFTParams *fft ){
    // Generate GAUSSIAN window
    int32_t n;

    for ( n=0; n<fft->NBUFFER; n++){
        fft->WND[n] = exp( -.5 * pow( (2.5*n/(fft->NBUFFER/2)), 2 ) );

    }

    fft->wndReady = 1;
    return 0;
}

uint32_t GenHannWin    ( sonofy_FFTParams *fft ){
    // Generate HANNING window
    int32_t n;
    for ( n=0; n < fft->NBUFFER; n++){
        fft->WND[n] = .5 * ( 1-cos( (2*M_PI*n)/(fft->NBUFFER-1) ) );

    }
    fft->wndReady = 1;
    return 0;
}

uint32_t genWND( FFTParams *fft ){
    // Generate analysis window
    switch ( fft->sonofy_WNDtype ) {
    case HANN:  GenHannWin( fft );
        break;
    case GAUSS: GenGaussWin( fft );
        break;
    default:    GenRectWin( fft );
        break;
    }
    return 0;
}

uint32_t sonofy_FFTComplex ( float *IQData, sonofy_FFTParams *fft ) {
    // Calculate Complex FFT from I-Q data
    int32_t j, k, c=0;
    float outRe, outIm;

    if ( !fft->twiddleReady )   calcTwiddle( fft );
    if ( !fft->wndReady )       genWND( fft );

    for(j=0; j < fft->NFFT; j++){

        outRe = 0.0;
        outIm = 0.0;
        for(k=0; k < fft->NBUFFER; k+=2){
            outRe += IQData[k] * fft->WND[c] * fft->twiddleRe[(j*c) % fft->NFFT] - IQData[k] * fft->WND[c] * fft->twiddleIm[(j*c) % fft->NFFT];
            outIm += IQData[k+1] * fft->WND[c] * fft->twiddleRe[(j*c) % fft->NFFT] + IQData[k+1] * fft->WND[c] * fft->twiddleIm[(j*c) % fft->NFFT];
        }
        fft->fftABS[j] = sqrt( pow(outRe,2) + pow(outIm,2) );
        fft->fftAngle[j] = atan( outIm/outRe );
    }
    return 0;

}

uint32_t sonofy_FFTReal ( float *IData, sonofy_FFTParams *fft ) {
    int32_t j, k;
    float outRe, outIm;

    if ( !fft->twiddleReady )   calcTwiddle( fft );
    if ( !fft->wndReady )       genWND( fft );

    for(j=0; j < fft->NFFT; j++){
        outRe = 0.0;
        outIm = 0.0;
        for(k=0; k < fft->NBUFFER; k++){
            outRe += IData[k] * fft->WND[k] * fft->twiddleRe[(j*k) % fft->NFFT];
            outIm += IData[k] * fft->WND[k] * fft->twiddleIm[(j*k) % fft->NFFT];
        }
        fft->fftABS[j] = sqrt( pow(outRe,2) + pow(outIm,2) );
        fft->fftAngle[j] = atan( outIm/outRe );
    }
    return 0;
}

uint32_t sonofy_initFFT         ( sonofy_FFTParams *f, uint16_t NFFT, uint16_t NBUFFER, sonofy_WNDtype WNDType ){
    // Init the FFT data struct
    f->NFFT        = NFFT;
    f->NBUFFER     = NBUFFER;
    f->WND         = (float*)malloc(sizeof(float)*NBUFFER);
    f->WNDType     = WNDType;
    f->twiddleReady= false;
    f->wndReady    = false;
    f->fftABS      = (float*)malloc(sizeof(float)*NFFT);
    f->fftAngle    = (float*)malloc(sizeof(float)*NFFT);
    f->twiddleIm   = (float*)malloc(sizeof(float)*NFFT);
    f->twiddleRe   = (float*)malloc(sizeof(float)*NFFT);

    genWND( f );

    return 0;
}
