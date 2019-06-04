//
//  fordFulkerson.h
//  hw3
//
//  Created by Emre Uysal on 05.05.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.
//

#ifndef fordFulkerson_h
#define fordFulkerson_h

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <limits>
#include "network.h"

using namespace std;

class FordFulkerson
{
public:
    int V;                  // vertice number
    vector<bool> marked;    // marked vector for bfs
    vector<Edge> edgeTo;    // for keeping edges
    double value;           // max flow value
    
    // constructor for setting parameters
    // finds max value but we don't need it
    FordFulkerson(Network G,int s,int t)
    {
        V = G.V;
        
        value = 0.0;
        
        vector<Edge> e1 = G.adjacency(t);
        for (vector<Edge>::iterator e = e1.begin(); e!= e1.end(); ++e)
        {
            (t == (*e).v) ? value -= (*e).v : value += (*e).v;
        }
        
        edgeTo.resize(G.V);
        marked.resize(G.V,false);
        while (bfs(G, s, t))
        {
            double path_flow = numeric_limits<double>::infinity();
            for (int v = t; v != s; v = edgeTo[v].endNode(v))
            {
                path_flow = min(path_flow, edgeTo[v].resCap(v));
            }

            for (int v = t; v != s; v = edgeTo[v].endNode(v))
            {
                edgeTo[v].addFlow(v, path_flow);
            }
            value += path_flow;
        }
    };
    
    // bfs algorithm for finding paths
    bool bfs(Network G, int s, int t)
    {
        queue<int> q;
        q.push(s);
        marked[s] = true;
        
        
        while (!q.empty() && !marked[t])
        {
            int v = q.front();
            q.pop();
            vector<Edge> e1 = G.adjacency(v);
            for (vector<Edge>::iterator e = e1.begin(); e!= e1.end(); ++e)
            {
                int w = (*e).endNode(v);
                if ((*e).resCap(w) > 0 && !marked[w])
                {
                    edgeTo[w] = (*e);
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
        return marked[t] ;
    };
    
};

#endif /* fordFulkerson_h */
