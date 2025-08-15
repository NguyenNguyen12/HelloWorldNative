
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)

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


void img_steno(char* message, char* filename) {

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

    int16_t raster_size = bmpHeader.real.bfSize - bmpHeader.real.bfOffBits;

    char* pix = (char*)malloc(raster_size);
    
    if (!pix) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }
    char* stupid_data = (char*)malloc(bmpHeader.real.bfOffBits);
    fread(stupid_data, bmpHeader.real.bfOffBits, 1,file);
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
    unsigned mask = 0b10000000;
    for (int i = 0; i < raster_size && message[(i / 8)] != '\0' ; i++) {
        
        //printf("Setting pixel %u with mask %u original is %u\n", i, mask, pix[i]);
        pix[i] = (pix[i] & 0b11111110) + ((message[i / 8] & mask) ? 1 : 0);
        //printf("Pixel %u after setting: %u\n", i, pix[i]);
        //printf("%c", message[i / 8]);
        mask = mask >> 1;
        if (mask == 0) {
            mask = 0b10000000;
        }
        

    }
        
    //rewrite data
    fwrite(bmpHeader.data, sizeof(bmpHeader.data), 1, outfile);
    fwrite(stupid_data, bmpHeader.real.bfOffBits, 1, outfile);
    fwrite(pix, raster_size, 1, outfile);

    //close and free
    fclose(outfile);
    free(pix);
    free(stupid_data);
}

void img_steno_decode(char* filename) {

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

    u_int16_t  raster_size = bmpHeader.real.bfSize - bmpHeader.real.bfOffBits;

    char* pix = (char*)malloc(raster_size);
    
    if (!pix) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }
    char* stupid_data = (char*)malloc(bmpHeader.real.bfOffBits);
    fread(stupid_data, bmpHeader.real.bfOffBits, 1,file);
    fread(pix, raster_size, 1, file);
    fclose(file);

    unsigned char mask = 0b10000000;
    unsigned char message[256];
    for (int i = 0; i < raster_size * 8 && pix[i-1] != '\0'; i++) {
        message[i/8] = (message[i/8] & ~mask) | ((pix[i] & 0b00000001) ? mask : 0);
        mask = mask >> 1;
        if (mask == 0) {
            mask = 0b10000000;
        }
        
    }
    printf("Decoded message: %s \n", message);

    free(pix);
    free(stupid_data);
}

void xor_key_message(char* key, char* ciphertext) {
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



