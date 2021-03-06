Linear Cryptanalysis
===================

The Cipher
----------

The first part of this project is implementing a toy cipher to perform
Linear Cryptanalysis on. The cipher under attack is a toy cipher that I
made up, christened TES (Toy Encrpytion Standard). 

TES is a block cipher with 4-bit blocks. It uses three rounds of a substitution
permutation network, where the S-Boxes are 4-bit to 4-bit.

I use a single 5-bit key that is expanded to 4 subkeys in the following
way: The i'th round subkey is the first 4 bits of the key, starting at the i'th
position, wrapping around to the beginning of the key when you reach the end.

So, for example, if the 5-bit key is 10111, the four subkeys will be:

    k0 = 1011
    k1 = 0111
    k2 = 1111
    k3 = 1110

The encryption process is as follows, where Pi is the i'th bit of the plaintext,
Kij is the j'th bit of the i'th subkey, Uij is the j'th bit of the i'th round
intermediate value, Ci is the i'th bit of the ciphertext.


         ---------------
        |P0 |P1 |P2 |P3 |
         ---------------
              -------
              | xor |
              -------
         ---------------
        |K00|K01|K02|K03|
         ---------------
                ||
                \/
         ---------------
        |    S-Box 1    |
         ---------------
                ||
                \/
         ---------------
        |    Permute    |
         ---------------
                ||
                \/
         ---------------
        |U10|U11|U12|U13|
         ---------------
              -------
              | xor | 
              -------
         ---------------
        |K10|K11|K12|K13|
         ---------------
                ||
                \/
         ---------------
        |    S-Box 2    |
         ---------------
                ||
                \/
         ---------------
        |    Permute    |
         ---------------
                ||
                \/
         ---------------
        |U20|U21|U22|U23|
         ---------------
              -------
              | xor | 
              -------
         ---------------
        |K20|K21|K22|K23|
         ---------------
                ||
                \/
         ---------------
        |    S-Box 3    |
         ---------------
                ||
                \/
         ---------------
        |    Permute    |
         ---------------
                ||
                \/
         ---------------
        |U30|U31|U32|U33|
         ---------------
              -------
              | xor | 
              -------
         ---------------
        |K30|K31|K32|K33|
         ---------------
                ||
                \/
         ---------------
        |C0 |C1 |C2 |C3 |
         ---------------


 I haven't done any testing to find optimal S-Boxes or permutations, so they're
 basically random right about now.

Analysis
--------

The overarching idea behind the attack is outlined in [this paper](http://luca-giuzzi.unibs.it/corsi/Support/papers-cryptography/Matsui.pdf) by Matsui. The idea is that the SBoxes display linear
behavior with some non-zero probability. By exploiting this slight bias,
we can derive a linear approximation for the first (n-1) rounds of the cipher,
which we can then use to check a guess for the subkey used in the last round.
If our guess is correct, the approximation should hold for a significant
number of ciphertexts partially deciphered using our guessed subkey. After finding
the n'th round subkey in this manner, we can construct an (n-2) round approximation
to recover the (n-1)th round subkey, and so on, until the entire key is recovered.

ToDo
====

Check the SBox approximations (do all the rows and columns add up to 8?)
Check the chaining. Are all chains valid chains?
Check the biases. Does a high bias really correspond to a good approximation?
