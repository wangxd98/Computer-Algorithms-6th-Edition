#ifndef MINCOST_
#define MINCOST_

#include "queue.h"
const int SE=2e5+5;

template <class Graph,class Edge>
static int cost(Graph &G)
{
    int x=0;
    for(int v=0;v<G.V();v++){
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
		    if(e->from(v)&& e->costRto(e->w())<INT_MAX)
                x+=e->flow()*e->costRto(e->w());
    }
    return x;
}

template <class Graph,class Edge> class MINCOST
{ 
    Graph &G;
    int s,t,flow;
    vector<int> wt;
    vector<Edge*> st;

    int ST(int v)const { 
	    if(st[v]==0){cout<<"error!"<<endl;return 0;}
        else return st[v]->other(v);
	}

    void augment(int s,int t)
    {    
	    int d=st[t]->capRto(t);
	    for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d)d=st[v]->capRto(v);
        if(d>flow)d=flow;
        st[t]->addflowRto(t,d);
        for(int v=ST(t);v!=s;v=ST(v))st[v]->addflowRto(v,d);
	    flow-=d;
    }
	
	bool shortest()
    {
        st.assign(G.V(),0);wt.assign(G.V(),INT_MAX);
        Queue<int> Q(2*G.V()+215);int N=0;
	    if(flow<=0)return false;
        wt[s]=0;
        Q.put(s);Q.put(G.V());

        while(!Q.empty()){ 
		    int v;
            while((v=Q.get())==G.V()){ 
			    if(N++>G.V())return(wt[t]<INT_MAX);
			    Q.put(G.V());
		    }
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
			    int w=e->other(v);
			    if(e->capRto(w)==0)continue;
                int P=wt[v]+e->wt(w);
                if(P<wt[w]){ 
			        wt[w]=P;
			        st[w]=e;Q.put(w);
		        }
		    }
	    }
        return(wt[t]<INT_MAX);
    }

public:
    MINCOST(Graph &G,int s,int t): 
	    G(G),s(s),t(t),flow(SE),st(G.V()),wt(G.V())
    { 
	    while(shortest())augment(s,t);
    }
};

#endif
