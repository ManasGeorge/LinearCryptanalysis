#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
const int numKnown = 16;

class Cipher{
private:
    int k;
    static int sbox = {7, 10, 6, 8, 13, 3, 12, 0, 15, 11, 5, 4, 1, 14, 9, 2};
    static int invsbox = {7, 12, 15, 5, 11, 10, 2, 0, 3, 14, 1, 9, 6, 4, 13, 8};
public:
    Cipher(int key){
        k = key;
        // sbox = {7, 10, 6, 8, 13, 3, 12, 0, 15, 11, 5, 4, 1, 14, 9, 2};
        // invsbox = {7, 12, 15, 5, 11, 10, 2, 0, 3, 14, 1, 9, 6, 4, 13, 8};
    }

    int round(int input){
        return sbox[k^input];
    }

    int invround(int input){
        return invround[input]^k;
    }
};

class Approximator{
private:
    int approximations[16][16];
    int bestInput;
    int bestOutput;
    int plains[];
    int ciphers[];
    Cipher c;
public:
    Approximator(Cipher in){
        c = in;
        for(int i = 0; i < 16; i++)
            for(int j = 0; j < 16; j++)
                approximations[i][j] = -8;

    void approximate(){
        for(left = 0; left < 16; left++)
            for(right = 0; right < 16; right++)
                for(in = 0; in < 16; in++)
                    if(mask(in,left) == mask(in, right))
                        approximations[right][left]++;

    void processplains(){
        int k1 = random() % 16;
        int k2 = random() % 16;

        for(int i = 0; i < numKnown; i++){
            plains[i] =  i;
            ciphers[i] = c.round(c.round(i,k1),k2);
        }
    }

    void linear();
    void brute();
    void showapprox(){
        printf("The approximations: ");
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
};


int main(){
    Cipher c;
    Approximator a(c);
    a.approximate();
    a.showapprox();
    // a.processplains();
    // a.testkeys();
}
