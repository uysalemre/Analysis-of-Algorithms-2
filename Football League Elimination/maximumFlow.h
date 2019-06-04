//
//  maximumFlow.h
//  hw3
//
//  Created by Emre Uysal on 05.05.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.


#ifndef maximumFlow_h
#define maximumFlow_h

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "fordFulkerson.h"

using namespace std;

class MaximumFlow
{
public:
    int numberOfTeams;                  // total team Number
    int numberOfMatches;                // total match Number
    int numOfV;                         // total Vertice Number
    vector<int> wins;                   // wins of teams
    vector<int> remaining;              // remaining matches of teams
    vector<vector<int> > gameSchedule;   // gameSchedule for teams
    vector<bool> isEliminated;          // for putting eliminated teams
    
    // default constructor
    MaximumFlow(){}
    
    // constructor for initializing
    MaximumFlow(int nT,int nM, vector<int> w, vector<int> remain, vector<vector<int> > gs)
    {
        numberOfTeams = nT;
        numberOfMatches = nM;
        wins = w;
        remaining = remain;
        gameSchedule = gs;

        for (int i = 0; i < numberOfTeams; i++)
        {
            isEliminated.push_back(false);
        }
       
        numOfV = numberOfMatches + numberOfTeams + 2;   // finding number of nodes for network
    }
    
    // finding the number of remaining matches for teams
    int against(int t1,int t2)
    {
        return gameSchedule[t1][t2];
    };

    // check function
    // checks the all teams are already eliminated or constructs flow network
    void check()
    {
        // calculate maximum win index
        int maxWin = 0;
        for (int i = 0; i < numberOfTeams; i++)
        {
            if (wins[maxWin] < wins[i])
            {
                maxWin = i;
            }
        }
        
        // for all teams fill the isEliminated array
        for (int x = 0; x < numberOfTeams ; x++)
        {
            // check the team is already eliminated or not
            if(wins[x] + remaining[x] < wins[maxWin])
            {
                isEliminated[x] = true;
            }
            else
            {
                // create a flow network
                Network fn(numOfV);
               
                // source
                int s = 0;
                // sink
                int t = numOfV - 1;
                
                // add edges teams -> t
                for (int i = 0; i < numberOfTeams; i++)
                {
                    if (i == x) continue; // no edge connect x
                    double capacity = wins[x] + remaining[x] - wins[i];
                    Edge fe(i, t, capacity);
                    fn.addEdge(fe);
                }
              
                // add edges matches -> teams
                int gameIndex = numberOfTeams;
                for (int i = 0; i < numberOfTeams - 1; i++)
                {
                    if (i == x) continue;
                    for (int j = i + 1; j < numberOfTeams; j++)
                    {
                        if (j == x) continue;
                        double capacity = std::numeric_limits<double>::infinity();
                        Edge ei(gameIndex, i, capacity);
                        Edge ej(gameIndex, j, capacity);
                        fn.addEdge(ei);
                        fn.addEdge(ej);
                        
                        // here add edges source -> matches
                        Edge eij(s, gameIndex, gameSchedule[i][j]);
                        fn.addEdge(eij);
                        gameIndex++;
                    }
                }
                // calculate ford fulkerson algorithm to find eliminated teams
                // if all capasity consumed team is not eliminated
                // otherwise it is eliminated
                FordFulkerson alg(fn,numOfV-2,numOfV-1);
                if (alg.marked[x])
                {
                    isEliminated[x] = true;
                }
            }
        }
    };    
};

#endif /* maximumFlow_h */
