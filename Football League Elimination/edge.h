//
//  edge.h
//  hw3
//
//  Created by Emre Uysal on 05.05.2019.
//  Copyright © 2019 Emre Uysal. All rights reserved.


#ifndef edge_h
#define edge_h

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Edge
{
    public:
        int v;              // from
        int w;              // to
        double capasity;    // capasity
        double flow;        // flow
    
        // default constructor
        Edge() {};
    
        // constructor with parameters
        Edge(int from, int to, double cap, double flw)
        {
            v = from;
            w = to;
            capasity = cap;
            flow = flw;
        };
    
        // constructor with parameters
        Edge(int from , int to , double cap)
        {
            v = from;
            w = to;
            capasity = cap;
            flow = 0.0;
        };
    
        // copy constructor that initializes an edge to another egde
        Edge(Edge const &e)
        {
            v = e.v;
            w = e.w;
            capasity = e.capasity;
            flow = e.flow;
        };
    
        // find the otherside node of given vertex
        int endNode(int vertex)
        {
            return (v == vertex) ? w : v;
        };
    
        // find residual capasity of an edge
        double resCap(int vertex)
        {
            return (vertex == v) ?  flow : capasity-flow;
        };
    
        // increase of decrease the flow
        void addFlow(int vertex, double delta)
        {
            (vertex == v) ? flow-=delta : flow+=delta;
        };
    
};

#endif /* Edge_h */
