#ifndef ANALYST_H
#define ANALYST_H

#include "cipher.h"
/*
 * What do I need with the Analyst class?
 * I should be able to pass it a Cipher, and have it figure out the key I'm using
 * Assumptions: maxinput is 64 bits
 *     Also, the cipher c must have an sbox method that takes the sbox index and an input
 *     Also, the cipher c must have a perms method that takes the perms index and an input
 *     Also, the cipher has three sboxes and three perms
 * Members
 */



class Analyst {
private:
    Cipher c;
    int bias[numBoxes][maxinput][maxinput];
    int bestApprox[numBoxes][maxinput];
    int totalApprox[maxinput];
    int plains[numKnown];
    int ciphers[numKnown];

    // Constructs known plain - cipher pairs
    void fillPairs();
    // Constructs approximation for sbox i
    void approxSBox(int i);
    // Mask represents a linear equation of the form X0 + X1 + X2 ... X(N-1),
    // where Xi is the i'th bit of the input and + is the xor operation
    // Parity returns the value of the expression represented by mask,
    // applied to the input.
    // The representation is as follows: The term Xi is included in the
    // expression above if the i'th bit of the mask is set. So, for example,
    // the expression X1 + X2 + X3 is represented by the mask with the
    // first, second, and third bits set - 14
    int parity(int mask, int input);
    // Chains the approximations found to the SBoxes to find an expression
    // that approximates the first 3 rounds of the cipher.
    void chainApproximations();
    // Takes the approximation for the first three rounds and uses it to
    // evaluate whether or not the decrypt results from a valid key guess
    // If it is a legitimate decrypt, the approximation should hold, and the
    // number of parity matches should be high.
    int parityScore (int plain, int decrypt);
    // For round i, fills bestApprox[i] with the best approximation for the
    // right hand side for a given lift hand side. Fills with -1 if none of
    // the right hand sides results in a non zero bias.
    void findBestApprox(int i);
    void printApprox(int i);
    void printBestApprox(int i);
    bool testKey(int i);
public:
    Analyst(const Cipher &cipher);
    int analyze();
};

#endif
