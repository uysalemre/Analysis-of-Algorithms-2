//
//  BinaryMultiplier.h
//  hw2
//
//  Created by Emre Uysal on 14.04.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.
//

#ifndef BinaryMultiplier_h
#define BinaryMultiplier_h

#include <iostream>

using namespace std;

class BinaryMultiplier
{
    public:
        string MakeMultiplication(string,string);
        string MakeShifting(string,int);
        string addBinary(string,string);
        void BinaryStringToDecimal(string);
};

#endif /* BinaryMultiplier_h */
