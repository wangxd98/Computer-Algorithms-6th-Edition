#ifndef MINCOST_
#define MINCOST_
//using std::queue

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

    int ST(int v)const 
	{ 
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
        for(int  v=ST(t);v!=s;v=ST(v))st[v]->addflowRto(v,d);
	    flow-=d;
    }
	
	bool shortest()
    {
        st.assign(G.V(),0);wt.assign(G.V(),INT_MAX);
		int N=0;
        queue<int> Q;
	    if(flow<=0)return false;
        wt[s]=0;
        Q.push(s);Q.push(G.V());
		while(!Q.empty()){ 
		    int v;
			while(!Q.empty()){ 
		        v=Q.front();Q.pop();
			    if(v== G.V()){
			    	if(N++ > G.V())return(wt[t]<INT_MAX);
				    Q.push(G.V());
				}
			    else break;
		    }
			adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
			    int w=e->other(v);
			    if(e->capRto(w)==0 )continue;
                int P=wt[v]+e->wt(w);
                if(P<wt[w]){ 
			        wt[w]=P;
					st[w]=e;Q.push(w);
		        }
		    }
	    }
        return(wt[t]<INT_MAX);
    }

public:
    MINCOST(Graph &G,int s,int t)
        : G(G),s(s),t(t),flow(SE),st(G.V()),wt(G.V())
    { 
	    while(shortest())augment(s,t);
    }
};

#endif
