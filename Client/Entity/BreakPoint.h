#ifndef UNTITLED1_BREAKPOINT_H
#define UNTITLED1_BREAKPOINT_H
#include <string>
#include<iostream>
using namespace std;
class BreakPoint {
public:
    string path;
    int rcvNum;
    int totalNum;

    inline double getProportion(){return rcvNum * 1.0 / (totalNum - 1);}
    inline void printString() {
        cout << endl << endl
            << "path:" + path << endl
            << "rcvNum:" + to_string(rcvNum) << endl
            << "totalNum:" + to_string(totalNum) << endl;          
    }
};


#endif //UNTITLED1_BREAKPOINT_H
