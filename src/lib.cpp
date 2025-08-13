#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <sstream> 

using namespace std;

#pragma pack(push, 1)

struct BGR_8bit_32 {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

union BMHeaderExtended {
    struct{
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
    }real;
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
    printf("img_copy called with");
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading.";
        return ;
    }

    BMHeaderExtended bmpHeader;

    file.read(bmpHeader.data, sizeof(bmpHeader.data));

    if (bmpHeader.real.biBitCount <= 8){
        //require color table, not implemented
        std::cout << "BMP file is small, less than 8 bit per pix,dont want to implement" << std::endl;
        return ;
    }
    unsigned int raster_size = bmpHeader.real.bfSize - bmpHeader.real.bfOffBits;

    char* pix = (char*)malloc(raster_size);

    file.read(pix, raster_size);
    file.close();

   

  
    printf("size of pix is: %lu\n", raster_size/bmpHeader.real.biWidth/ bmpHeader.real.biHeight);
    printf("size of raster is: %lu\n", raster_size);
    
    std::ofstream outfile("out.bmp", std::ios::binary);
    if (!file) {
        cerr << "Error opening file write.";
        return ;
    }

    outfile.write(bmpHeader.data, sizeof(bmpHeader.data));
    outfile.write(pix, raster_size);
    outfile.close();
    free(pix);
}

void xor_key_message(char* key, char* ciphertext) {
    //both are strings, so we can use them directly
    char* cipthertext = (char*)malloc(sizeof(key));
    for (size_t i = 0; i < strlen(key); ++i) {
        cipthertext[i] = key[i] ^ ciphertext[i % strlen(ciphertext)];
        return;
    }
    return;

}