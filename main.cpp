#include "cipher.h"
#include "analyst.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    Cipher c(14);
    Analyst a(c);
    a.analyze();
}
