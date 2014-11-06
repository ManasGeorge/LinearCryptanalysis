Linear Cryptanalysis
===================

The first part of this project is implementing a toy cipher to perform
Linear Cryptanalysis on. The cipher under attack is a toy cipher that I
made up, christened TES (Toy Encrpytion Standard). 

TES is a block cipher with 6-bit blocks. It uses three rounds of a substitution
permutation network, where the S-Boxes are 6-bit to 6-bit.

I use a single 7-bit key that is expanded to 4 subkeys in the following
way: The i'th round subkey is the first 6'bits of the key, starting at the i'th
position, wrapping around to the beginning of the key when you reach the end.

So, for example, if the 7-bit key is 1011101, the four subkeys will be:
    k1 = 011101
    k2 = 111011
    k3 = 110110
    k4 = 101101

The encryption process is as follows, where Pi is the i'th bit of the plaintext,
Kij is the j'th bit of the i'th subkey, Uij is the j'th bit of the i'th round
intermediate value, Ci is the i'th bit of the ciphertext.

 ---------------------------
|P0 |P1 |P2 |P3 |P4 |P5 |P6 |
 ---------------------------
          -------
          | xor |
          -------
 ---------------------------
|K10|K11|K12|K13|K14|K15|K16|
 ---------------------------
            ||
            \/
 ---------------------------
|        S-Box 1            |
 ---------------------------
            ||
            \/
 ---------------------------
|        Permute            |
 ---------------------------
            ||
            \/
 ---------------------------
|U20|U21|U22|U23|U24|U25|U26|
 ---------------------------
          -------
          | xor |
          -------
 ---------------------------
|K20|K21|K22|K23|K24|K25|K26|
 ---------------------------
            ||
            \/
 ---------------------------
|        S-Box 2            |
 ---------------------------
            ||
            \/
 ---------------------------
|        Permute            |
 ---------------------------
            ||
            \/
 ---------------------------
|U30|U31|U32|U33|U34|U35|U36|
 ---------------------------
          -------
          | xor |
          -------
 ---------------------------
|K30|K31|K32|K33|K34|K35|K36|
 ---------------------------
            ||
            \/
 ---------------------------
|        S-Box 3            |
 ---------------------------
            ||
            \/
 ---------------------------
|        Permute            |
 ---------------------------
            ||
            \/
 ---------------------------
|U40|U41|U42|U43|U44|U45|U46|
 ---------------------------
          -------
          | xor |
          -------
 ---------------------------
|K40|K41|K42|K43|K44|K45|K46|
 ---------------------------
            ||
            \/
 ---------------------------
|C0 |C1 |C2 |C3 |C4 |C5 |C6 |
 ---------------------------

 I haven't done any testing to find optimal S-Boxes or permutations, so they're
 basicaly random right about now.
