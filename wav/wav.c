//#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "windows.h"

#define CHUNK_ID_SIZE 4

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    char FormType[CHUNK_ID_SIZE];
} RIFF;

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    unsigned short AudioFormat;
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitsPerSample;
} FMT;

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    char Type[CHUNK_ID_SIZE];
    char *String;
} LIST;

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    char *String;
} INFO;

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    char *String;
} JUNK;

typedef struct {
    char ID[CHUNK_ID_SIZE];
    unsigned int Size;
    int *Data32bit;
    
} DATA;

typedef struct {
    RIFF RIFF;
    FMT FMT;
    LIST LIST;
    INFO INFO;
    JUNK JUNK;
    DATA DATA;
    unsigned long file_size;
} WAVE;

void PrintFilePos(FILE *wav) {
    int file_pos = ftell(wav);
    printf("file_pos: \t\t%i\n", file_pos);
}

int main(void) {
    FILE *wav = NULL;
    errno_t err;
    //err = fopen_s(&wav, "sounds/sine_44k_16b_1ch.wav", "rb");
    //err = fopen_s(&wav, "sounds/ambient-swoosh.wav", "rb");
    //err = fopen_s(&wav, "sounds/resonant-twang.wav", "rb");
    //err = fopen_s(&wav, "sounds/sine_192k_32b_2ch.wav", "rb");
    //err = fopen_s(&wav, "sounds/vocal-hah.wav", "rb");
    //err = fopen_s(&wav, "sounds/synthetic-gib.wav", "rb");
    //err = fopen_s(&wav, "sounds/Master-192k-2ch-32b.wav", "rb");

    if(err != 0) {
        perror("fopen\n");
    }

    WAVE wav1 = {0};
    wav1.DATA.Data = NULL;
    char chunk_id[CHUNK_ID_SIZE];
    int count = 0;
    INFO INFO;

    fseek(wav, 0, SEEK_END);
    wav1.file_size = ftell(wav);
    rewind(wav);
    do {
        count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
        if(ferror(wav)) {
            perror("read error\n");
        }
        fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);

        if(strncmp(chunk_id, "RIFF", CHUNK_ID_SIZE) == 0) {
            count = fread_s(&wav1.RIFF.ID, sizeof(wav1.RIFF.ID), 1, sizeof(wav1.RIFF.ID), wav);
            count = fread_s(&wav1.RIFF.Size, sizeof(wav1.RIFF.Size), 1, sizeof(wav1.RIFF.Size), wav);
            count = fread_s(&wav1.RIFF.FormType, sizeof(wav1.RIFF.FormType), 1, sizeof(wav1.RIFF.FormType), wav);
            printf("ID: \t\t\t%.4s\n", &wav1.RIFF.ID);
            printf("Size: \t\t\t%u\n", wav1.RIFF.Size);
            printf("FormType: \t\t%.4s\n", &wav1.RIFF.FormType);
            continue;
        }

        if(strncmp(chunk_id, "fmt ", CHUNK_ID_SIZE) == 0) {
            count = fread_s(&wav1.FMT.ID, sizeof(wav1.FMT.ID), 1, sizeof(wav1.FMT.ID), wav);
            count = fread_s(&wav1.FMT.Size, sizeof(wav1.FMT.Size), 1, sizeof(wav1.FMT.Size), wav);
            count = fread_s(&wav1.FMT.AudioFormat, sizeof(wav1.FMT.AudioFormat), 1, sizeof(wav1.FMT.AudioFormat), wav);
            count = fread_s(&wav1.FMT.NumChannels, sizeof(wav1.FMT.NumChannels), 1, sizeof(wav1.FMT.NumChannels), wav);
            count = fread_s(&wav1.FMT.SampleRate, sizeof(wav1.FMT.SampleRate), 1, sizeof(wav1.FMT.SampleRate), wav);
            count = fread_s(&wav1.FMT.ByteRate, sizeof(wav1.FMT.ByteRate), 1, sizeof(wav1.FMT.ByteRate), wav);
            count = fread_s(&wav1.FMT.BlockAlign, sizeof(wav1.FMT.BlockAlign), 1, sizeof(wav1.FMT.BlockAlign), wav);
            count = fread_s(&wav1.FMT.BitsPerSample, sizeof(wav1.FMT.BitsPerSample), 1, sizeof(wav1.FMT.BitsPerSample), wav);
            printf("ID: \t\t\t%.4s\n", &wav1.FMT.ID);
            printf("Size: \t\t\t%u\n", wav1.FMT.Size);
            printf("AudioFormat: \t%u\n", wav1.FMT.AudioFormat);
            printf("NumChannels: \t%u\n", wav1.FMT.NumChannels);
            printf("SampleRate: \t%u\n", wav1.FMT.SampleRate);
            printf("ByteRate: \t\t%u\n", wav1.FMT.ByteRate);
            printf("BlockAlign: \t%u\n", wav1.FMT.BlockAlign);
            printf("BitsPerSample: \t%u\n", wav1.FMT.BitsPerSample);
            continue;
        }

        if(strncmp(chunk_id, "LIST", CHUNK_ID_SIZE) == 0) {
            count = fread_s(&wav1.LIST.ID, sizeof(wav1.LIST.ID), 1, sizeof(wav1.LIST.ID), wav);
            count = fread_s(&wav1.LIST.Size, sizeof(wav1.LIST.Size), 1, sizeof(wav1.LIST.Size), wav);
            count = fread_s(&wav1.LIST.Type, sizeof(wav1.LIST.Type), 1, sizeof(wav1.LIST.Type), wav);
            if(strncmp(wav1.LIST.Type, "INFO", CHUNK_ID_SIZE) == 0) {
                while(1) {
                    count = fread_s(&INFO.ID, sizeof(INFO.ID), 1, sizeof(INFO.ID), wav);
                    count = fread_s(&INFO.Size, sizeof(INFO.Size), 1, sizeof(INFO.Size), wav);
                    INFO.String = malloc(INFO.Size);
                    count = fread_s(INFO.String, INFO.Size, 1, INFO.Size, wav);
                    printf("%.4s \t\t\t%s\n", &INFO.ID, INFO.String);
                    free(INFO.String);
                    if(INFO.Size % 2) {
                        fseek(wav, 1, SEEK_CUR);
                    }
                    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
                    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
                    if(strncmp(chunk_id, "data", 4) == 0) {
                        break;
                    }
                }
            }
            else {
                printf("unknown list type\n");
            }
            printf("ID: \t\t\t%.4s\n", &wav1.LIST.ID);
            printf("Size: \t\t\t%u\n", wav1.LIST.Size);
            printf("Type: \t\t\t%.4s\n", &wav1.LIST.Type);
            continue;
        }

        // TODO finish junk chunk - sometimes has data in junk??
        if((strncmp(chunk_id, "JUNK", CHUNK_ID_SIZE) == 0) || (strncmp(chunk_id, "junk", CHUNK_ID_SIZE) == 0)) {
            count = fread_s(&wav1.JUNK.ID, sizeof(wav1.JUNK.ID), 1, sizeof(wav1.JUNK.ID), wav);
            count = fread_s(&wav1.JUNK.Size, sizeof(wav1.JUNK.Size), 1, sizeof(wav1.JUNK.Size), wav);
            fseek(wav, wav1.JUNK.Size, SEEK_CUR);
            printf("ID: \t\t\t%.4s\n", &wav1.JUNK.ID);
            printf("Size: \t\t\t%u\n", wav1.JUNK.Size);
            continue;
        }

        if(strncmp(chunk_id, "data", 4) == 0) {
            count = fread_s(&wav1.DATA.ID, sizeof(wav1.DATA.ID), 1, sizeof(wav1.DATA.ID), wav);
            count = fread_s(&wav1.DATA.Size, sizeof(wav1.DATA.Size), 1, sizeof(wav1.DATA.Size), wav);
            printf("ID: \t\t\t%.4s\n", &wav1.DATA.ID);
            printf("Size: \t\t\t%u\n", wav1.DATA.Size);
            wav1.DATA.Data = malloc(wav1.DATA.Size);
            int total_count = 0;
            for(size_t i = 0; i < wav1.DATA.Size / sizeof(*wav1.DATA.Data); i++) {
                count = fread_s(&wav1.DATA.Data[i], wav1.DATA.Size, sizeof(*wav1.DATA.Data), 1, wav);
                printf("Data[%i]: \t\t%i\n", i, wav1.DATA.Data[i]);
                total_count += count;
            }
            free(wav1.DATA.Data);
            printf("total_count: \t\t%i\n", total_count);
            break;
        }
    }
    while(1);

    fclose(wav);

    printf("program success\n");
    return 0;
}
