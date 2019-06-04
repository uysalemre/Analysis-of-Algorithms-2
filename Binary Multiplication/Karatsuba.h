//
//  Karatsuba.h
//  hw2
//
//  Created by Emre Uysal on 15.04.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.
//

#ifndef Karatsuba_h
#define Karatsuba_h

#include <iostream>
#include <vector>

using namespace std;

class Karatsuba
{

public:
    int lengthController(string &,string &);
    string addStrings(string,string);
    string multiply(string,string);
    string DecimalToBinary(long long int);
    string Subtraction(string,string);
    string MakeShifting(string,int);
    
};

#endif /* Karatsuba_h */
