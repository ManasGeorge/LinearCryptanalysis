#ifndef TES_H
#define TES_H

// What are the internals like?
//      SBoxes = 6-bit => 64, so int arrays of length 64
//          SBoxes array indexed by round
//      Inverse SBoxes
//      Permutation = int array of length 64, maps one 6-bit input to another
//          Permutation array indexed by round
//      Inverse permutations
//
//      Round function that takes round as argument
//          The round function changes the state variable, updating it according to
//          the round index
//
//      Encrypt function
//      Decrypt function

const static int maxinput = 16;
const static int numKnown = 16;
const static int numBoxes = 3;
const static int blocksize = 4;

class Cipher {
private:
    static int SBoxes[numBoxes][maxinput];
    static int invSBoxes[numBoxes][maxinput];
    static int Perms[numBoxes][maxinput];
    static int invPerms[numBoxes][maxinput];
    int state;
    int keys[4];
    int key;

    void genKeys();
    int rol(int i, int j);
public:
    Cipher(int key);
    Cipher(const Cipher &c);
    int encrypt(int plain);
    int decrypt(int cipher);
    int round(int i);
    int invRound(int i);
    int sbox(int i, int j);
    int perms(int i, int j);
};

#endif


