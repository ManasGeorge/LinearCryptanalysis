#include "analyst.h"
#include <cstdlib>

Analyst::Analyst(Cipher cipher) : c(cipher) {
}

int Analyst::analyze() {
    int key = 0;
    int score[maxinput];

    for (int i = 0 ; i < numBoxes; i++)
        approxSBox(i);

    for (int i = 0; i < numBoxes; i++)
        findBestApprox(i);

    chainApproximations();

    for (int guess = 0; guess < maxinput; guess++) {
        score[guess] = 0;

        for (int i  = 0 ; i < numKnown; i ++) {
            int decrypt = ciphers[i] ^ guess;
            score[guess] += countParityMatch(plains[i], decrypt);
        }
    }

    return key;
}

void Analyst::fillPairs() {
    for (int i = 0; i < maxinput; i++) {
        plains[i] = rand() % maxinput;
        ciphers[i] = c.encrypt(plains[i]);
    }
}

void Analyst::approxSBox(int i) {
    for (int left = 0; left < maxinput; left++)
        for (int right = 0; right < maxinput; right++) {
            bias[i][left][right] = -8;

            for (int input = 0; input < maxinput; input++)
                if (parity(left, input) == parity(right, input))
                    bias[i][left][right]++;

            bias[i][left][right] *= bias[i][left][right];
        }
}

int Analyst::parity(int mask, int input) {
    int inter = mask & input;
    int ret = 0;

    while (inter) {
        inter &= (inter - 1);
        ret++;
    }

    return ret;
}

void Analyst::chainApproximations() {
    // Lefts holds the left hand side for the next approximation
    int lefts[maxinput];

    // The lefts for the first round are simply all possible left hand sides,
    // in order
    for (int i = 0; i < maxinput; i++)
        lefts[i] = i;

    for (int i = 0; i < numBoxes; i++)
        for (int j = 0; j < maxinput; j++) {
            int left = lefts[j];
            if(left != -1) {
                int right = bestApprox[i][left];
                if(right == -1)
                    lefts[j] = -1;
                else
                    lefts[j]  = c.perms(i, right);
            }
        }

    for(int i = 0; i < maxinput; i++)
        totalApprox[i] = lefts[i];
}
