
#include "FordFulkerson.h"
//#include "preflow.h"

template <class Graph,class Edge> class BMATCHING
{
    const Graph &G;
public:
    BMATCHING(const Graph &G,int N1):G(G)
    {
        int s,t,maxflow=0;
	    Graph F(G.V()+2,1);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
            F.insert(e);
        }
	    s=G.V();t=G.V()+1;
        for(int i=0;i<N1;i++)
            F.insert(new EDGE(s,i,1));
        for(int i=N1;i<s;i++)
            F.insert(new EDGE(i,t,1));
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
        cout<<maxflow<<endl;
        for(int i=0;i<N1;i++){
            adjIterator<Edge> A(F,i);
            for(EDGE* e=A.beg();!A.end();e=A.nxt())
                if(e->flow()==1 &&  e->from(i)&& e->capRto(i)==1 )
                    cout<<e->v()+1<<" "<<e->w()+1<<endl;
	    }
    }
};
