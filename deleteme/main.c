#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#define CHUNK_ID_SIZE 4

typedef struct {
    unsigned char *ID;
    unsigned int *Size;
    unsigned char *FormType;
} RIFF;

typedef struct {
    RIFF riff;
    unsigned int *file_size;
} WAVE;


int main(void) {
    FILE *wave_file;
    errno_t err;
    err = fopen_s(&wave_file, "sounds/ambient-swoosh.wav", "rb");
    assert(err == 0);
    fseek(wave_file, 0, SEEK_END);
    int file_size = ftell(wave_file);
    rewind(wave_file);
    WAVE *wave;
    wave = malloc(file_size);
    wave->file_size = file_size;
    printf_s("%u\n", wave->file_size);
    int count = 0;
    wave->riff.ID = wave;
    count = fread_s(&wave->riff.ID, CHUNK_ID_SIZE, sizeof(*wave->riff.ID), CHUNK_ID_SIZE, wave_file);
    printf("%4s\n", &wave->riff.ID);
    wave->riff.Size = wave->riff.ID + CHUNK_ID_SIZE;
    count = fread_s(&wave->riff.Size, CHUNK_ID_SIZE, sizeof(*wave->riff.Size), 1, wave_file);
    printf("%u\n", wave->riff.Size);
    wave->riff.FormType = wave->riff.Size + CHUNK_ID_SIZE;
    count = fread_s(&wave->riff.FormType, CHUNK_ID_SIZE, sizeof(*wave->riff.ID), CHUNK_ID_SIZE, wave_file);
    printf("%4s\n", &wave->riff.FormType);
    return 0;
}