#include "analyst.h"
#include <cstdlib>
#include <cstdio>

Analyst::Analyst(const Cipher &cipher) : c(cipher) {
}

int Analyst::analyze() {
    int key = 0;
    int score[maxinput];
    printf("Approximating SBoxes\n");

    for (int i = 0 ; i < numBoxes; i++) {
        approxSBox(i);
        printApprox(i);
    }

    printf("Finding best SBox approximations\n");

    for (int i = 0; i < numBoxes; i++) {
        findBestApprox(i);
        printBestApprox(i);
    }

    printf("Chaining Approximations\n");
    chainApproximations();
    printf("Guessing final key\n");

    for (int guess = 1; guess < maxinput; guess++) {
        score[guess] = 0;

        for (int i  = 0 ; i < numKnown; i ++) {
            int decrypt = ciphers[i] ^ guess;
            score[guess] += countParityMatch(plains[i], decrypt);
        }
    }

    for (int i = 1; i < maxinput; i++)
        if (score[i] > score[key])
            key = i;

    printf("The guessed final key is: %d\n", key);
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

            for (int input = 0; input < maxinput; input++){
                int output = c.sbox(i,input);
                if (parity(left, input) == parity(right, output))
                    bias[i][left][right]++;
            }

            // bias[i][left][right] *= bias[i][left][right];
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
    for (int i = 1; i < maxinput; i++)
        lefts[i] = i;

    for (int i = 1; i < numBoxes; i++)
        for (int j = 1; j < maxinput; j++) {
            if (lefts[j] != -1) {
                int right = bestApprox[i][lefts[j]];

                if (right == -1)
                    lefts[j] = -1;
                else
                    lefts[j]  = c.perms(i, right);
            }
        }

    for (int i = 1; i < maxinput; i++)
        totalApprox[i] = lefts[i];
}

int Analyst::countParityMatch(int plain, int decrypt) {
    int ret = 0;

    for (int left  = 1; left  < maxinput; left ++) {
        int right = totalApprox[left];

        if (right != -1)
            if (parity(left, plain) == parity(right, decrypt))
                ret++;
    }

    return ret;
}

void Analyst::findBestApprox(int i) {
    for (int left = 1; left < maxinput; left++) {
        int max = 0;

        for (int right = 1; right < maxinput; right++)
            if (bias[i][left][right] > bias[i][left][max])
                max = right;

        bestApprox[i][left] = (bias[i][left][max] == 0) ? (-1) : (max);
    }
}

void Analyst::printApprox(int i) {
    printf("%3s", "");

    for (int j = 0; j < maxinput; j++)
        printf("%3d", j);

    printf("\n");

    for (int j = 0; j < maxinput; j++) {
        printf("%3d", j);

        for (int k = 0; k < maxinput; k++)
            printf("%3d", bias[i][j][k]);

        printf("\n");
    }

    printf("\n");
}

void Analyst::printBestApprox(int i) {
    for (int j = 0; j < maxinput; j++)
        printf("%d -> %d\n", j, bestApprox[i][j]);

    printf("\n");
}
