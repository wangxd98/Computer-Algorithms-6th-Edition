#ifndef MINCOST_
#define MINCOST_

#include "queue.h"
//#include "FordFulkerson.h"
#include "preflow.h"

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
    int s,t;
    vector<int> wt;
    vector <Edge *> st;
  
    int ST(int v)const { 
	    if(st[v]==0){cout<<"error!"<<endl;return 0;}
        else return st[v]->other(v);
	}

    void augment(int s,int t)
    { 
	    int d=st[t]->capRto(t);
	    for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d)d=st[v]->capRto(v);
        st[t]->addflowRto(t,d);
        for( int v=ST(t);v!=s;v=ST(v))st[v]->addflowRto(v,d);
    }

    int negcyc()
	{
	    for(int i=0;i<G.V();i++){
		    int neg=negcyc(i);
			if(neg>=0)return neg;
	    }
	    return -1;
    }

    int negcyc(int ss)
	{
        st.assign(G.V(),0);wt.assign(G.V(),INT_MAX);
        Queue<int> Q(2*G.V()+515);int N=0;
		wt[ss]=0.0;
        Q.put(ss);Q.put(G.V());
        while(!Q.empty()){ 
	        int v;
		    while((v=Q.get())== G.V()){ 
			    if(N++ > G.V())return -1;
			    Q.put(G.V());
		    }
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
		        int w=e->other(v);
			    if(e->capRto(w)==0 )continue;
			    double P=wt[v]+e->wt(w);
			    if(P<wt[w]){ 
			        wt[w]=P;
				    for( int node_test=v;(st[node_test]!=0 && node_test!=ss);node_test=ST(node_test)){ 
				        if( ST(node_test)== w ){
					        st[w]=e;
						    return w;
				        }
			        }
				    st[w]=e;Q.put(w);
			    }
		    }
	    }
        return -1;
    }

public:
    MINCOST(Graph &G,int s,int t)
        : G(G),s(s),t(t),st(G.V()),wt(G.V())
    { 
	    int flow=0;
		MAXFLOW<Graph,Edge>(G,s,t,flow);
        for(int x=negcyc();x!=-1;x=negcyc())augment(x,x);
    }
};

#endif
