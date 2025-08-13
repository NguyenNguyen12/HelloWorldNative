#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void myfun(char* name);

int bit_shift_right(int value, int shift);
int bit_shift_left(int value, int shift);
void img_copy(const char* message, const char* filename);
void xor_key_message(const char* key, const char* ciphertext);

#endif
