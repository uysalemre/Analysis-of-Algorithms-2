//
//  BinaryMultiplier.cpp
//  hw2
//
//  Created by Emre Uysal on 14.04.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.
//

#include "BinaryMultiplier.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string BinaryMultiplier::MakeMultiplication(string str1, string str2)
{
    string allSum = "";
    for (int j = 0 ; j<str2.length(); j++)
        {
            int secondDigit = str2[j] - '0';
            if (secondDigit == 1)
            {
                string shifted = MakeShifting(str1,str2.size()-(j+1));
                allSum = addBinary(shifted, allSum);
            }
            else
            {
                continue;
            }
            
        }
    return allSum;
}

string BinaryMultiplier::addBinary(string a, string b)
{
    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum

    
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Comput sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);
        
        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;
        
        // Compute carry
        s /= 2;
        
        // Move to next digits
        i--;
        j--;
    }
    return result;
}

string BinaryMultiplier::MakeShifting(string str, int stepnum)
{
    string shifted = str;
    for (int i = 0 ; i < stepnum ; i++)
        shifted = shifted + '0';
    return shifted;
}


void BinaryMultiplier::BinaryStringToDecimal(string result)
{
    cout<<"Binary Result : "<<result<<endl;
    unsigned long long int val = 0;
    for (int i = result.length()-1; i >= 0; i--)
    {
        if (result[i] == '1')
        {
            val += pow(2,(result.length()-1)-i);
        }
    }
    cout<<"Decimal Result (Not proper for Large Binary Numbers):" <<val<<endl;
}
