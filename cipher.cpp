#include "cipher.h"

Cipher::Cipher(int k){
    k = key;
    genKeys();
    //ToDo Set up the SBoxes, Perms, and their inverses
}
    
void Cipher::genKeys(){
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

int Cipher::round(int i){
    if(i == 3){
        return state ^ keys[3];
    } else {
        int a = state ^ keys[i];
        int b = SBoxes[i][a];
        int c = Perms[i][b];
        return c;
    }
}

int Cipher::invRound(int i){
    if(i == 0){
        return state ^ keys[0];
    } else {
        int a = state ^ keys[i];
        int b = invPerms[i][a];
        int c = invSBoxes[i][b];
        return c;
    }
}

int Cipher::encrypt(int plain){
    state = plain;
    for(int i = 0; i < 4; i++)
        round(i);
    return state;
}

int Cipher::decrypt(int cipher){
    state = cipher;
    for(int i = 3; i >= 0; i--){
        invRound(i);
    return state;
}

int Cipher::sbox(int i, int j)
