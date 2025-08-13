// scroll to the end to see myfunc

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)

struct BGR_8bit_32 {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

union BMHeaderExtended {
    struct {
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReserved1;
        uint16_t bfReserved2;
        uint32_t bfOffBits;
        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    } real;
    char data[54];
};

#pragma pack(pop)

int bit_shift_right(int value, int shift) {
    return value >> shift;
}

int bit_shift_left(int value, int shift) {
    return value << shift;
}

void img_copy(const char* message, const char* filename) {
    printf("img_copy called");

    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening infile.\n");
        return;
    }

    union BMHeaderExtended bmpHeader;
    fread(bmpHeader.data, sizeof(bmpHeader.data), 1, file);

    if (bmpHeader.real.biBitCount <= 8) {
        fprintf(stderr, "BMP file is less than or equal to 8 bits per pixel; not implemented.\n");
        fclose(file);
        return;
    }

    unsigned int raster_size = bmpHeader.real.bfSize - bmpHeader.real.bfOffBits;

    char* pix = (char*)malloc(raster_size);
    if (!pix) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fseek(file, bmpHeader.real.bfOffBits, SEEK_SET);
    fread(pix, raster_size, 1, file);
    fclose(file);

    printf("Size of pixel: %u\n", raster_size / (bmpHeader.real.biWidth * bmpHeader.real.biHeight));
    printf("Size of raster: %u\n", raster_size);

    FILE* outfile = fopen("out.bmp", "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file.\n");
        free(pix);
        return;
    }

    fwrite(bmpHeader.data, sizeof(bmpHeader.data), 1, outfile);
    fwrite(pix, raster_size, 1, outfile);

    fclose(outfile);
    free(pix);
}

void xor_key_message(const char* key, const char* ciphertext) {
    size_t key_len = strlen(key);
    size_t cipher_len = strlen(ciphertext);
    char* result = (char*)malloc(key_len + 1);

    if (!result) {
        printf("Malloc failed.\n");
        return;
    }

    for (size_t i = 0; i < key_len; ++i) {
        result[i] = key[i] ^ ciphertext[i];
    }
    result[key_len] = '\0';

    printf("XOR Result: %s\n", result);
    free(result);
}

void myfun(char* name) {
    printf("My name is %s\n", name);
}
