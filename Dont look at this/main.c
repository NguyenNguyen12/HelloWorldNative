#include "mylib.h"

int main() {

    char* filename = (char*)"img.bmp";
    char* message = (char*)"ImAnImposter";
    img_steno(message, filename);

    char* decode_filename = (char*)"out.bmp";
    img_steno_decode(decode_filename);
    printf("\n\n\n\n");
    
}