//
//  main.cpp
//  hw2
//
//  Created by Emre Uysal on 14.04.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.

#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
#include "BinaryMultiplier.h"
#include "Karatsuba.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // get the binary numbers as strings
    string firstNumber,secondNumber,outputFile;
    if (!argv[1])
    {
        cout<<"Please give a output FileName in Format : ./executable <filename.txt>"<<endl;
        return 1;
    }
    cout<<"Please give the First Binary number : ";
    cin>>firstNumber;
    cout<<endl<<"Please give the Second Binary number : ";
    cin>>secondNumber;
    
    // make the initial lengths equal by adding zeros
    int len1 = firstNumber.size();
    int len2 = secondNumber.size();
    int general_len = firstNumber.size();
    
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            firstNumber = '0' + firstNumber;
        general_len = firstNumber.size();
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            secondNumber = '0' + secondNumber;
        general_len = secondNumber.size();
    }
    
    // In classical methodology Binary String Multiplication
    cout<<"Classical Algorithm : "<<endl;
    BinaryMultiplier newobj;
    const clock_t classical_time = clock();
    string classic = newobj.MakeMultiplication(firstNumber, secondNumber);
    cout << float( clock () - classical_time ) /  CLOCKS_PER_SEC<<endl<<endl;
    float c_time = float( clock () - classical_time ) /  CLOCKS_PER_SEC;
    newobj.BinaryStringToDecimal(classic);
    
    // Using Karatsuba Multiplication Algorithm Binary String Multiplication
    cout<<endl<<"Karatsuba Algorithm : "<<endl;
    Karatsuba obj;
    const clock_t karatsuba_time = clock();
    string karatsuba = obj.multiply(firstNumber, secondNumber);
    cout << float( clock () - karatsuba_time ) /  CLOCKS_PER_SEC<<endl<<endl;
    float k_time = float( clock () - classical_time ) /  CLOCKS_PER_SEC;
    newobj.BinaryStringToDecimal(karatsuba);
    
    
    ofstream TimeResults;
    TimeResults.open(argv[1], ios::out | ios::app);
    if (TimeResults.is_open())
    {
        TimeResults<<c_time<<"\t"<<k_time<<"\t"<<general_len<<endl;
    }
    else
    {
        cout<<"Can not open the file"<<endl;
        return 1;
    }
    cout<<"Time and Bit results are written into "<<argv[1]<<endl;
    TimeResults.close();
    
    return 0;
}
