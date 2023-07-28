#pragma once
#define ACCURACY 5
#define SINGLE_MAX 10000
#define EXPONENT_MAX 1000
#define BUF_SIZE 1024
int modpow(long long a, long long b, int c);

int jacobi(int a, int n);

int solovayPrime(int a, int n);

int probablePrime(int n, int k);

int randPrime(int n);

int gcd(int a, int b);

int randExponent(int phi, int n);

int inverse(int n, int modulus);

int readFile(FILE* fd, char** buffer, int bytes);

int encode(int m, int e, int n);

int decode(int c, int d, int n);

int* encodeMessage(int len, int bytes, char* message, int exponent, int modulus);

int* decodeMessage(int len, int bytes, int* cryptogram, int exponent, int modulus);
