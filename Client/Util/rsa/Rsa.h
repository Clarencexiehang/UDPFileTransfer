#pragma once
#ifndef _RSA_H_
#define _RSA_H_
#include<string>
#include"crsa.h"
#include <iostream>
#include<vector>
using namespace std;

class Rsa
{
private:
    int psk, prk, module/*, nbyte*/;
public:
    inline int getPsk() { return psk; }
    inline int getPrk() { return prk; }
    inline int getModule() { return module; }
    inline void printKey() {
        cout << "psk:" << psk << "  prk:" << prk << "  module:" << module << endl;
    }
    inline void ini() {
        int p, q, phi;
        while (1) {
            p = randPrime(SINGLE_MAX);
            q = randPrime(SINGLE_MAX);
            module = p * q;
            if (module >= 128) break;
        }
       /* if (module >> 21) nbyte = 3;
        else if (module >> 14) nbyte = 2;
        else nbyte = 1;*/
        phi = (p - 1) * (q - 1);
        psk = randExponent(phi, EXPONENT_MAX);
        prk = inverse(psk, phi);
    }

    

    inline vector<long>* encrypt(vector<long>* m) {
        vector<long>* c = new vector<long>;
        //cout << "开始加密" << endl;
        for (int i = 0; i < m->size(); i++)
        {
            long a=modpow((*m)[i], psk, module);
            //cout << a << " ";
            c->push_back(a);
        }
        return c;
    }

    //堆内存返回
    inline vector<long>* decrypt(vector<long>* c) {
        vector<long>* m = new vector<long>;
        //cout << "开始解密\n";
        for (int i = 0; i < c->size(); i++)
        {
            long a=modpow((*c)[i], prk, module);
            //cout << a << " ";
            m->push_back(a);
        }
        return m;
    }



    inline void setPsk(int psk, int module) {
        this->psk = psk;
        this->module = module;
        /*if (module >> 21) nbyte = 3;
        else if (module >> 14) nbyte = 2;
        else nbyte = 1;*/
    }

    inline void printVector(vector<long>* v) {
        for (long ch : *v) {
            cout << ch << " ";
        }
        cout << endl;
    }

    inline string vecConverter(vector<long>* sequence) {
        string result;
        for (long o:*sequence)
        {
            result += (char)o;
        }
        return result;
    }
    
};


#endif