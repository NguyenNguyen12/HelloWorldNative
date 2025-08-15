#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void img_steno(char* message, char* filename);
void img_steno_decode(char* filename);
void xor_key_message(char* key, char* ciphertext);
void myfun(char* name);

#endif
