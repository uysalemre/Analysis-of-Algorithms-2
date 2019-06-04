//
//  Karatsuba.cpp
//  hw2
//
//  Created by Emre Uysal on 15.04.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Karatsuba.h"
#include "BinaryMultiplier.h"

int Karatsuba::lengthController(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1;
}

string Karatsuba::addStrings(string first, string second)
{
    string result;  // To store the sum bits
    
    // make the lengths same before adding
    int length = lengthController(first, second);
    int carry = 0;  // Initialize carry
    
    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';
        
        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';
        
        result = (char)sum + result;
        
        // boolean expression for 3-bit addition
        carry = (firstBit&secondBit) | (secondBit&carry) | (firstBit&carry);
    }
    
    // if overflow, then add a leading 1
    if (carry)
    {
        result = '1' + result;
    }
    
    return result;
}

string Karatsuba::DecimalToBinary(long long int number)
{
    string result = "";
    if (number <= 0)
    {
        return "0";
    }
    else
    {
        int i = 0;
        while (number > 0)
        {
        
            long long int num= number % 2;
            stringstream ss;
            ss<<num;
            result = ss.str() + result;
            number = number / 2;
            i++;
        }
        return result;
        
    }
}

string Karatsuba::Subtraction(string lhs, string rhs)
{
    
    int length = lengthController(lhs, rhs);
    int diff;
    string result;

    for (int i = length-1; i >= 0; i--)
    {
        diff = (lhs[i]-'0') - (rhs[i]-'0');
        if (diff >= 0)
        {
            result = DecimalToBinary(diff) + result;
           // result.insert(0, to_string(diff));
        }
        else
        {
            for (int j = i-1; j>=0; j--)
            {
                lhs[j] = ((lhs[j]-'0') - 1) % 10 + '0';
                if (lhs[j] != '1')
                {
                    break;
                }
            }
            result = DecimalToBinary(diff+2) + result;
        }
    }
    return result;
}

string Karatsuba::MakeShifting(string str, int stepnum)
{
    string shifted = str;
    for (int i = 0 ; i < stepnum ; i++)
        shifted = shifted + '0';
    return shifted;
}


string Karatsuba::multiply(string X,  string Y)
{
    int n = lengthController(X, Y);
    
    if (n == 1) return ((Y[0]-'0' == 1) && (X[0]-'0' == 1)) ? "1" : "0";
    
    int fh = n/2;   // First half of string, floor(n/2)
    int sh = (n-fh); // Second half of string, ceil(n/2)
    
    // Find the first half and second half of first string.
    string Xl = X.substr(0, fh);
    string Xr = X.substr(fh, sh);
    
    // Find the first half and second half of second string
    string Yl = Y.substr(0, fh);
    string Yr = Y.substr(fh, sh);
    
    // Recursively calculate the three products of inputs of size n/2
    string P1 = multiply(Xl, Yl);
    string P2 = multiply(Xr, Yr);
    string P3 = multiply(addStrings(Xl, Xr), addStrings(Yl, Yr));
   
    // return added string version
    return addStrings(addStrings(MakeShifting(P1, 2*(n-n/2)),P2),MakeShifting(Subtraction(P3,addStrings(P1,P2)), n-(n/2)));
}

//10010101010101001010100101010101
//10101010110101010101

//10000101011001000110110101001010000101010110001000110010110000100101100011011001
