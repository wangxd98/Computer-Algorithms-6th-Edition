// Ford Fulkerson method
#ifndef Fulkerson_
#define Fulkerson_

#define M 6553555;
#include "pq.h"

template <class Graph,class Edge> class MAXFLOW
{
    const Graph &G;
    int s,t,maxf;
    vector<int> wt;
    vector<Edge *> st;
    int ST(int v)const{return st[v]->other(v);}
    void augment(int s,int t)
	{
	    int d=st[t]->capRto(t);
        for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d)
                d=st[v]->capRto(v);
        st[t]->addflowRto(t,d);
	    maxf+=d;
        for(int v=ST(t);v!=s;v=ST(v))
            st[v]->addflowRto(v,d);
    }
	bool pfs();
public:
    MAXFLOW(const Graph &G,int s,int t,int &maxflow): G(G),s(s),t(t),st(G.V()),wt(G.V()),maxf(0)
   {
	    while(pfs())augment(s,t);
		maxflow+=maxf;
	}
};

template <class Graph,class Edge>
bool MAXFLOW<Graph,Edge>::pfs()
{
    PQ<int> pQ(G.V(),wt);
    for(int v=0;v<G.V();v++){
	    wt[v]=0;st[v]=0;pQ.insert(v);
	}
    wt[s]=M;pQ.change(s);
    while(!pQ.empty()){
	    int v=pQ.deletemax();wt[v]=M;
        if(v==t||(v!=s&&st[v]==0))break;
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
		    int w=e->other(v);
            int cap=e->capRto(w);
            int P=cap<wt[v]?cap:wt[v];
            if(cap>0&&P>wt[w]){
			    wt[w]=P;pQ.change(w);st[w]=e;
			}
        }
    }
    return st[t]!=0;
}

#endif