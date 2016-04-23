/*
 * libsonofy - utils-file
 * sonofy_wavefiles.h
 *
 * Read and write wave files
 * 2016, Alessio Degani <alessio.degani@gmail.com>
 *
 */

#ifndef LIBSONOFY_WAVEFILE_H
#define LIBSONOFY_WAVEFILE_H

#include <inttypes.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef enum {MEMERR, NOTFOUND, NOTWAVE, NOTPCM, BROKFILE, BROKHEAD} wERR;

typedef struct _sonofy_wHeader{
    char     chunkID[4];
    uint32_t chunkSize;
    char     format[4];
    char     subChunkID[4];
    uint32_t subChunkSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char     dataChunkID[4];
    uint32_t dataChunkSize;
} sonofy_wHeader;

#ifdef __cplusplus
extern "C" {
#endif

//sonofy_wHeader *header;

uint16_t sonofy_wavread(char *fileName, int16_t **samples, sonofy_wHeader *header);
uint16_t sonofy_wavwrite(char *fileName, int16_t *samples, sonofy_wHeader *header);

#ifdef __cplusplus
}
#endif

#endif // LIBSONOFY_WAVEFILE_H