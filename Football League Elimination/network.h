//
//  network.h
//  hw3
//
//  Created by Emre Uysal on 05.05.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.


#ifndef network_h
#define network_h

#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include "edge.h"

class Network
{
public:
    int V;                      // vertice number
    int E;                      // edge number
    vector<vector<Edge> > adj;   // adjacency matrix for network
    
    // default constructor
    Network(){};
    
    // constructor takes vertice number
    Network(int vertice)
    {
        V = vertice;
        E = 0;
        adj.resize(V);
    };
    
    // edge adding function for network
    void addEdge(Edge e)
    {
        adj[e.v].push_back(e);
        adj[e.w].push_back(e);
        E++;
    };
    
    // function for returning an edge vector
    vector<Edge> adjacency(int v)
    {
        return adj[v];
    };
    
};

#endif /* network_h */
