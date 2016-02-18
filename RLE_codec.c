#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode(FILE *fptIn, FILE *fptOut);
void decode(FILE *fptIn, FILE *fptOut);

int main(int argc, char *argv[]){
    FILE *fptIn;
    FILE *fptOut;

    if(argc!=4) {
        printf("usage: RLEcodec 'e|d' 'fileNameIn' ' fileNameOut'");
        exit(0);
    }

    fptIn = fopen(argv[2], "rb");
    fptOut = fopen(argv[3], "wb");

    if(strcmp(argv[1], "e") == 0){
        encode(fptIn, fptOut);
    } else if(strcmp(argv[1], "d") == 0){
        decode(fptIn, fptOut);
    } else {
        printf("second argument must be c or d");
        exit(0);
    }

	return 0;
}

void encode(FILE *fptIn, FILE *fptOut){
    unsigned char c;
    unsigned char p;
    unsigned char count = 1;

    fread (&p, 1, 1, fptIn);
    fread (&c, 1, 1, fptIn);

    do{
        if(p == c){
            count++;
            if(count == 255){
                fprintf(fptOut, "%c%c", count-1, p);
                count = 1;
            }
        } else {
            fprintf(fptOut, "%c%c", count, p);
            count = 1;
        }
        p=c;
    }while(fread (&c , 1, 1, fptIn) == 1);
	fprintf(fptOut, "%c%c", count, p);
}

void decode(FILE *fptIn, FILE *fptOut){
    unsigned char c;
    unsigned char count;
    int i;

    while(fread (&count, 1, 1, fptIn) == 1){
        fread(&c, 1, 1, fptIn);

        for(i=0; i<count; i++) fwrite(&c, 1, 1, fptOut);
    }
}
