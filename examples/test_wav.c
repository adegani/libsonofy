#include <stdio.h>
#include "../utils-file/sonofy_wavefile.h"

void main(){
	sonofy_wHeader header;

	int16_t *samples = NULL;

    wERR err = sonofy_wavread("440.wav", &samples, &header);

    if ( err != 0 ){
		printf("err: %d\n", err);
	}else{

		printf("Channel count: \t%d \n",    header.numChannels);
		printf("Sample rate: \t%d Hz\n", 	header.sampleRate);
		printf("Samples format: %d bit\n", header.bitsPerSample);

		for (uint16_t i = 0; i < 5; i++)
			printf("Sample[%d]: %d\n", i, samples[i]);
		}
}
