#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;
const int numKnown = 16;
int sbox[] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
int invsbox[] = {14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
int approximations[16][16];
int plains[numKnown];
int ciphers[numKnown];

int round(int in, int key){
    return sbox[in^key];
}

int invround(int in, int key){
    return sbox[in]^key;
}

int mask(int value, int mask){
    int inter = value & mask;
    int ret = 0;
    while(inter > 0){
        int temp = inter % 2;
        ret ^= temp;
        inter /= 2;
    }
    return ret;
}

void showapprox(){
    int i,j;
    printf("The approximations:\n");
    cout << "\t";
    for(i = 0 ; i < 16; i ++)
        cout << i << "\t";
    cout << "\n";

    for(i = 0 ; i < 16; i ++){
        cout << i << "\t";
        for(j=0; j<16; j++)
            cout << approximations[i][j] << "\t";
        cout <<"\n";
    }
}

void approximate(){
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 16; j++)
            approximations[i][j] = -8;

    int left, right, in;
    for(left = 0; left < 16; left++)
        for(right = 0; right < 16; right++)
            for(in = 0; in < 16; in++)
                if(mask(left,sbox[in]) == mask(in, right))
                    approximations[right][left]++;
}

void processplains(){
    int k1 = rand() % 16;
    int k2 = rand() % 16;

    for(int i = 0; i < numKnown; i++){
        plains[i] =  i;
        ciphers[i] = round(round(i,k1),k2);
    }
}

void find_best_approx(int &bl, int &br){
    int max_bias = -8;
    for(int i = 1; i < 16; i ++)
        for(int j = 1; j < 16; j ++)
            if(approximations[i][j] > max_bias){
                bl = i;
                br = j;
                max_bias = approximations[i][j];
            }
}


int main(){	
    approximate();
    showapprox();
    int bl,br;
    find_best_approx(bl,br);
    cout << bl << " " << br << endl;
}
