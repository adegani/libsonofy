/*
 * libsonofy - utils-file
 * sonofy_wavefiles.c
 *
 * Read and write wave files
 * 2016, Alessio Degani <alessio.degani@gmail.com>
 *
 */

#include "sonofy_wavefile.h"

uint16_t sonofy_wavread(char *fileName, int16_t **samples, sonofy_wHeader *header){
    int fd;

    char chunkID[4];
    uint32_t chunkSize;
    uint32_t chunkPtr;
    uint32_t fmtPtr, fmtSize;
    uint32_t dataPtr, dataSize;

    if ((fd = open(fileName, O_RDONLY)) < 1)
        return NOTFOUND;

    if (read(fd, header, 12) < 12)
        return BROKHEAD;

    if (strncmp(header->chunkID, "RIFF", 4) ||
        strncmp(header->format, "WAVE", 4))
        return NOTWAVE;

    // Seek all chunks in the wave file
    while (1){ // TODO: FIX this!!
        chunkPtr = lseek(fd,0,SEEK_CUR);
        if (read(fd, &chunkID, 4)<4) break;
        if (read(fd, &chunkSize,4)<4) break;

        // If the chunk is "fmt ", save the pointer of the fmt chunk
        if (strncmp(chunkID,"fmt ",4) == 0){
            fmtPtr = chunkPtr;
            fmtSize = chunkSize;
        }

        // If the chunk is "data", save the pointer of the data chunk
        if (strncmp(chunkID,"data",4) == 0){
            dataPtr = chunkPtr;
            dataSize = chunkSize;
        }

        // Ignore all of the other chunks
        lseek(fd, chunkSize, SEEK_CUR);
    }

    // Read the fmt chunk
    lseek(fd, fmtPtr,SEEK_SET);
    read(fd, &header->subChunkID, fmtSize+8 );

    if (header->audioFormat != 1)
        return NOTPCM;

    // Read the data Chunk
    lseek(fd, dataPtr,SEEK_SET);
    read(fd, &header->dataChunkID, 8 );

    if (*samples) free(*samples);
    *samples = (int16_t*)malloc(header->dataChunkSize);

    if (!*samples)
        return MEMERR;

    if (read(fd, *samples, header->dataChunkSize) < header->dataChunkSize)
        return BROKFILE;

    close(fd);
    return 0;
}
uint16_t sonofy_wavwrite(char *fileName, int16_t *samples, sonofy_wHeader *header){
    int fd;
    if ((fd = creat(fileName, 0666)) < 1)
        //errx(1, "Error creating file");
    //if (write(fd, header, sizeof(sonofy_wHeader)) < sizeof(sonofy_wHeader))
        //errx(1, "Error writing header");
    //if (write(fd, samples, header.dataChunkSize) < header.dataChunkSize)
        //errx(1, "Error writing samples");
    close(fd);
    return 0;
}