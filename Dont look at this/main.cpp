
#include "mylib.h";

int main() {

    char* filename = (char*)"img.bmp";
    img_copy("asdasdasd", filename);

    char* key = "8234j923414";
    char* ciphertext = "asdfsadfgD";
    xor_key_message(key, ciphertext);
    printf("%s\n", ciphertext);

    return 0;
}