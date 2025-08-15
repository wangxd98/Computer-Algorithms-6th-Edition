#ifndef ConsecLP_
#define ConsecLP_

#include "cycles1.h"
//#include "cycles2.h"

template <class Graph,class Edge> 
class ConsecLP 
{
    Graph &G;
public:
        ConsecLP(Graph &G,int s,int t):G(G)
	    {
	    	MINCOST<Graph,Edge>(G,s,t);
            int maxf=0;
            adjIterator<Edge> A(G,s);
            for(EDGE* e=A.beg();!A.end();e=A.nxt())
	            if(e->from(s)) maxf+=e->flow();
	        cout<<cost<GRAPH<Edge>,Edge>(G)<<endl;
	    }
};

#endif
