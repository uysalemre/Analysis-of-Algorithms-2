//
//  main.cpp
//
//  Created by Emre Uysal on 5.05.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <queue>
#include "maximumFlow.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // check if filename given or not
    if (!argv[1])
    {
        cout << "No input file given ! "<<endl;
        return 1;
    }
    
    int teamNum = 0;                // for keeping team number from file
    vector<int> currentScores;      // for keeping current scores from file
    vector<vector<int> > matrix;    // matrix of matches left
   
    // read from file
    ifstream input;
    input.open(argv[1]);
    if (input.is_open())
    {
        string n;
        getline(input,n);
        teamNum = atoi(n.c_str());
        
        // read the current scores in here
        for (int i = 0 ; i < teamNum; i++)
        {
            string score;
            (i == teamNum-1) ? getline(input, score, '\n') : getline(input,score,' ');
            currentScores.push_back(atoi(score.c_str()));
        }
        
        // read the remaining matches matrix in here
        for (int i = 0; i < teamNum; i++)
        {
            vector<int> line;                   // vector for keeping the line
            for (int j = 0; j < teamNum; j++)
            {
                string num;
                (j == teamNum-1) ? getline(input, num, '\n') : getline(input,num,' ');
                line.push_back(atoi(num.c_str()));
            }
            matrix.push_back(line);
        }
    }
    else
    {
        cout<<"Can not open "<<argv[1]<<endl;
        return 1;
    }
    
    
//    // Informations related the given input file for debug.
//    cout << "Team Number : " <<teamNum<<endl<<endl;
//
//    cout << "Current Scores : ";
//    for (int k = 0 ; k < currentScores.size(); k++)
//    {
//        cout << currentScores[k] << " ";
//    }
//    cout<<endl;
//    cout<<endl<<"Remaining Matches : "<<endl<<endl;
    
    vector<int> remaining;
    remaining.resize(teamNum);
    for (int i = 1 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j < i; j++)
        {
            // calculate remaining matches for teams
            if(matrix[i][j] > 0)
            {
                // for debug you can remove the comment to see matches between teams
                //cout<<"Team "<< j <<" vs " <<"Team "<< i << " => NumOfMatch : "<<matrix[i][j]<<endl;
                remaining[j] += matrix[i][j];
                remaining[i] += matrix[i][j];
            }
        }
    }
    
    // calculate total match number for all teams
    int matchNum = 0;
    for (int i = 0; i < remaining.size(); i++)
    {
        // remove comment to see which team has how many matches
        //cout << i <<". "<<remaining[i]<<endl;
        matchNum += remaining[i];
    }

    // find if teams eliminated or not
    // then print the team can win if it is not eliminated
    MaximumFlow obj(teamNum,matchNum,currentScores,remaining,matrix);
    obj.check();
    
    // if output file is given write result to output
    if (argv[2])
    {
        ofstream out;
        out.open(argv[2]);
        if (out.is_open())
        {
            cout<<"Result is written into "<<argv[2]<<endl;
            for (int i= 0; i<teamNum; i++)
            {
                if (!obj.isEliminated[i])
                {
                    out<<1<<" ";
                }
                else
                {
                    out<<0<<" ";
                }
            }
        }
        else
        {
            cout<<"Can not open output file !"<<endl;
            return 1;
        }
    }
    else
    {
        for (int i= 0; i<teamNum; i++)
        {
            if (!obj.isEliminated[i])
            {
                cout<<1<<" ";
            }
            else
            {
                cout<<0<<" ";
            }
        }
    }
    cout<<endl;
    return 0;
}
