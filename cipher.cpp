#include "cipher.h"
#include <cstdio>

int Cipher::SBoxes[numBoxes][maxinput] = {
    {8, 15, 6, 4, 13, 5, 10, 9, 12, 3, 1, 2, 7, 14, 11, 0},
    {7, 8, 6, 3, 9, 12, 13, 1, 2, 14, 10, 11, 5, 4, 0, 15},
    {3, 9, 6, 14, 5, 10, 4, 2, 13, 12, 1, 0, 7, 15, 8, 11}
};

int Cipher::invSBoxes[numBoxes][maxinput];
int Cipher::Perms[numBoxes][maxinput] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
};

int Cipher::invPerms[numBoxes][maxinput];

Cipher::Cipher(int k) {
    key = k;
    genKeys();

    for (int i  = 0; i < maxinput; i++) {
        for (int j = 0; j < 3; j++) {
            invSBoxes[j][SBoxes[j][i]] = i;
            invPerms[j][Perms[j][i]] = i;
        }
    }
}

Cipher::Cipher(const Cipher &c) {
    key = c.key;
    genKeys();

    for (int i  = 0; i < maxinput; i++)
        for (int j = 0; j < 3; j++) {
            invSBoxes[j][SBoxes[j][i]] = i;
            invPerms[j][Perms[j][i]] = i;
        }
}

void Cipher::genKeys() {
    for(int i = 0; i< 4; i++)
    {
        keys[i] = rol(key, i) >> 1;
        printf("Key %d is %d\n",i,keys[i]);
    }
}

int Cipher::round(int i) {
    if (i == 3)
        return state ^ keys[3];
    else {
        int a = state ^ keys[i];
        int b = SBoxes[i][a];
        int c = Perms[i][b];
        return c;
    }
}

int Cipher::invRound(int i) {
    if (i == 0)
        return state ^ keys[0];
    else {
        int a = state ^ keys[i];
        int b = invPerms[i][a];
        int c = invSBoxes[i][b];
        return c;
    }
}

int Cipher::encrypt(int plain) {
    state = plain;

    for (int i = 0; i < 4; i++)
        round(i);

    return state;
}

int Cipher::decrypt(int cipher) {
    state = cipher;

    for (int i = 3; i >= 0; i--)
        invRound(i);

    return state;
}

int Cipher::sbox(int i, int j) {
    return SBoxes[i][j];
}

int Cipher::perms(int i, int j) {
    return Perms[i][j];
}

int Cipher::rol(int i, int j){
    int mask = (1 << (blocksize + 2)) - 1;
    int lmsb = (i << j) & (!mask);
    return ((i << j) & (mask)) | (lmsb >> (blocksize+2));
}
