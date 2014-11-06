#include "cipher.h"
int Cipher::SBoxes[3][64] = { {0, 28, 17, 10, 19, 43, 7, 56, 53, 36, 63, 52, 1, 42, 5, 33, 48, 39, 50, 51, 38, 8, 14, 11, 59, 25, 31, 46, 2, 58, 16, 60, 21, 55, 35, 37, 45, 54, 26, 4, 34, 44, 41, 24, 30, 62, 12, 40, 27, 20, 18, 3, 32, 6, 22, 49, 29, 9, 61, 23, 57, 47, 15, 13},
    {0, 6, 11, 36, 13, 42, 25, 3, 53, 4, 46, 27, 35, 57, 24, 41, 28, 44, 61, 38, 59, 20, 8, 33, 32, 40, 43, 14, 50, 16, 55, 5, 34, 45, 48, 22, 2, 31, 23, 30, 60, 56, 26, 12, 58, 62, 51, 54, 17, 52, 21, 9, 63, 37, 18, 10, 49, 39, 47, 1, 15, 19, 29, 7},
    {13, 33, 22, 16, 50, 53, 47, 37, 6, 32, 0, 26, 44, 24, 61, 46, 34, 63, 30, 49, 39, 20, 35, 18, 14, 58, 11, 51, 38, 60, 9, 31, 62, 5, 25, 21, 36, 12, 43, 40, 7, 4, 59, 1, 19, 56, 28, 15, 57, 23, 10, 2, 52, 45, 41, 3, 54, 29, 42, 55, 8, 48, 17, 27}
};

int Cipher::Perms[3][64] = {
    {24, 33, 57, 30, 46, 29, 40, 22, 37, 44, 60, 28, 52, 31, 26, 3, 5, 59, 42, 14, 49, 34, 9, 36, 15, 39, 13, 6, 63, 55, 53, 41, 35, 19, 48, 10, 62, 0, 23, 61, 45, 51, 12, 16, 4, 8, 58, 21, 47, 17, 56, 7, 54, 11, 25, 38, 2, 43, 27, 1, 32, 50, 18, 20},
    {31, 16, 1, 23, 46, 55, 44, 25, 40, 15, 6, 9, 3, 54, 8, 26, 59, 30, 0, 42, 60, 52, 24, 5, 53, 14, 10, 49, 33, 41, 61, 48, 39, 51, 57, 58, 63, 38, 36, 4, 17, 50, 7, 28, 19, 43, 35, 2, 27, 11, 20, 37, 47, 12, 56, 45, 62, 22, 18, 34, 21, 29, 13, 32},
    {32, 29, 19, 56, 18, 16, 0, 39, 17, 63, 51, 34, 44, 13, 59, 43, 20, 5, 54, 48, 36, 57, 26, 47, 15, 60, 62, 28, 12, 42, 23, 24, 41, 7, 30, 61, 1, 25, 10, 46, 27, 37, 53, 33, 9, 40, 11, 21, 4, 55, 6, 22, 14, 8, 58, 49, 38, 35, 3, 52, 50, 2, 31, 45}
};

int Cipher::invSBoxes[3][64] = {};
int Cipher::invPerms[3][64] = {};

Cipher::Cipher(int k) : blocksize(64) {
    k = key;
    genKeys();

    for (int i  = 0; i < blocksize; i++)
        for (int j = 0; j < 3; j++) {
            invSBoxes[j][SBoxes[j][i]] = i;
            invPerms[j][Perms[j][i]] = i;
        }
}

void Cipher::genKeys() {
    //key = 1234567
    //k1 = 234567
    int k1 = key << 1;
    //k2 = 345671
    int k2 = (k1 << 1) + ((key & 128) >> 6);
    //k3 = 456712
    int k3 = (k2 << 1) + ((key & 64 >> 5));
    //k4 = 567123
    int k4 = (k3 << 1) + ((key & 32 >> 4));
    keys[0] = k1;
    keys[1] = k2;
    keys[2] = k3;
    keys[3] = k4;
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






