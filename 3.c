#include <stdio.h>
#include <math.h>

int gcd(int a, int b);
int modInverse(int a, int m);
void generateSignature(int message, int privateKey, int* r, int* s, int p, int q, int g);

int main() {
    int p = 23; // Prime number
    int q = 11; // Prime factor of p-1
    int g = 4;  // Generator g < p
    int privateKey = 5; // Example private key
    int publicKey = 16; // Example public key (g^privateKey % p)
    int message = 7; // Example message
    int r, s;

    generateSignature(message, privateKey, &r, &s, p, q, g);

    printf("Message: %d\n", message);
    printf("Signature: (r, s) = (%d, %d)\n", r, s);

    return 0;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

void generateSignature(int message, int privateKey, int* r, int* s, int p, int q, int g) {
    int k = 3; // Example random value k
    *r = ((int)pow(g, k) % p) % q;
    int k_inv = modInverse(k, q);
    *s = (k_inv * (message + privateKey * (*r))) % q;
}
