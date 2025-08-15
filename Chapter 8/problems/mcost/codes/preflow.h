#ifndef Preflow_
#define Preflow_

#include "gq.h"
const int wtM=5555500;

template <class Graph,class Edge> class MAXFLOW
{
    const Graph &G;
    int s,t;
    vector<int> h,wt,st;
    GQ<int> gQ;

    void initheights()
    {
	    h[s]=G.V();
    }

    void push(Edge* e,int v,int w,int f)
    {
        e->addflowRto(w,f);
        wt[v] -= f;wt[w]+=f;
    }

    void relabel(int v)
    {
        if(v!=s && v!=t && wt[v]>0){
            int hv=INT_MAX;
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
		        int w=e->other(v);
                if( e->residual(v)&& h[w]<hv)hv=h[w];
		    }
		    if(hv<INT_MAX && hv>=h[v]){
		    	h[v]=hv+1;
		        gQ.put(v);st[v]=1;
			}
	    }
    }

    void discharge(int v)
    {
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
		    int w=e->other(v);
            int cap=e->capRto(w);
            int P=cap<wt[v]?cap:wt[v];
            if(P>0 &&(v==s || h[v]==h[w]+1)){
		        push(e,v,w,P);
                if((w!=s)&&(w!=t)&&(!st[w])){
			        gQ.put(w);
					st[w]=1;
			    }
            }
        } 
    }

    void wtmax()
    {
	    adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
		    if(e->from(s))wt[s]+=e->cap();
		if(wt[s]<0 || wt[s]>wtM)wt[s]=wtM;
    }

    void heights()
    {
        queue<int> qu;
		for(int i=0;i<G.V();i++)h[i]=0;
	    qu.push(t);
        // 广度优先搜索
		while(!qu.empty()){
		    int v=qu.front();qu.pop();
            // 搜索与顶点v相连的边
			adjIterator<Edge> A(G,v);
			for(Edge* e=A.beg();!A.end();e=A.nxt()){
			    int w=e->other(v);
				if( h[w]==0 && e->residual(w)){
				    h[w]=h[v]+1;
					qu.push(w); 
			    }
	        } 
	    } 
	    h[s]=G.V();
    }
    
public:
    MAXFLOW(Graph &G,int s,int t,int &maxflow): 
        G(G),s(s),t(t),h(G.V(),0),wt(G.V(),0),st(G.V(),0),gQ(G.V())
    {
	    heights();
		wtmax();
        gQ.put(s);st[s]=1;
        while(!gQ.empty()){
	        int v=gQ.get();
	        st[v]=0;
            discharge(v);
            relabel(v);
		}
	    maxflow+=wt[t];
    }
};

#endif
