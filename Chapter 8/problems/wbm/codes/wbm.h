#ifndef ASSIGNMENT_
#define ASSIGNMENT_

//#include "cycles.h"
//#include "cycles1.h"
//#include "cycles2.h"
//#include "simplex.h"
#include "shortest1.h"
//#include "shortest2.h"

template <class Graph,class Edge> class ASSIGNMENT
{ 
    Graph &G;
public:
    ASSIGNMENT(Graph &G):G(G)
    { 
        int s=G.V(),t=G.V()+1,n=s/2;
	    Graph F(G.V()+2,1);
		for (int v=0;v<G.V();v++){
            adjIterator<Edge>A(G,v);
            for (Edge* e=A.beg();!A.end();e=A.nxt())
                F.insert(e);
        }
		for(int i=0;i<n;i++)F.insert(new EDGE(s,i,1,0));
		for(int i=n;i<s;i++)F.insert(new EDGE(i,t,1,0));
		MINCOST<Graph,Edge>(F,s,t);
        int maxf=0;
        adjIterator<Edge> A(F,s);
        for(EDGE* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxf+=e->flow();
	    cout<<maxf<<" "<<cost<GRAPH<Edge>,Edge>(G)<<endl;
    }
};

#endif
