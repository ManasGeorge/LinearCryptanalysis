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

class Cipher {
  private:
    const int blocksize = 64;
    static int SBoxes[3][64];
    static int invSBoxes[3][64];
    static int Perms[3][64];
    static int invPerms[3][64];
    int state;
    int keys[4];
    int key;

    void genKeys();
  public:
    Cipher(int key);
    int encrypt(int plain);
    int decrypt(int cipher);
    int round(int i);
    int invRound(int i);
    int sbox(int i, int j);
};

#endif

