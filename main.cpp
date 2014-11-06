#include "cipher.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    Cipher a(40);
    cout << "Encrypting 5" << endl;
    cout << a.decrypt(a.encrypt(5)) << endl;
}
