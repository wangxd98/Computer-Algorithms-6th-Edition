#ifndef GRAPH_
#define GRAPH_

class EDGE
{
    int pv,pw,pcap,pcost,pflow;
public:
    EDGE(int v,int w,int cap,int cost=0):pv(v),pw(w),pcap(cap),pcost(cost),pflow(0){}
    int v()const{return pv;}
    int w()const{return pw;}
    int cap()const{return pcap;}
    int cost()const{return pcost;}
    int wt(int v)const{return from(v)? -pcost:pcost;}
    int flow()const{return pflow;}
    bool from(int v)const{return pv==v;}
    bool residual(int v)const
    {
	    return(pv==v&&pcap-pflow>0||pw==v&&pflow>0 );
	}
	int other(int v)const{return from(v)? pw:pv;} 
    int capRto(int v)const{return from(v)? pflow:pcap-pflow;}
    int costRto(int v)const{return from(v)? -pcost:pcost;}
    void addflowRto(int v,int d){pflow+=from(v)?-d:d;}
};

template <class Edge> class GRAPH
{
    int Vcnt,Ecnt;bool digraph;
    vector< vector<Edge *> >adj;
public:
    GRAPH(int V,bool digraph=false):adj(V+1),Vcnt(V),Ecnt(0),digraph(digraph)
    {
      for(int i=0;i<=V;i++)
        adj[i].assign(V+1,0);
    }
    GRAPH(){}
	int V()const{return Vcnt;}
	int E()const{return Ecnt;}
    Edge* edge(int v,int w)const{return adj[v][w];}
	void insert(Edge *e)
    {
	    int v=e->v(),w=e->w();
		if(adj[v][w]==0)Ecnt++;
		adj[v][w]=e;
		if(!digraph)adj[w][v]=e;
    }
};

template <class Edge>
class adjIterator
{
    const GRAPH<Edge> &G;
    int i,j,v;
public:
    adjIterator(const GRAPH<Edge> &G,int v): G(G),v(v),i(0),j(0){}
    Edge *beg()
	{
	    i=-1;j=-1 ;return nxt();
	}
    Edge *nxt()
    {
	    for(i++;i<G.V();i++)
            if(G.edge(v,i))return G.edge(v,i);
	    for(j++;j<G.V();j++)
            if(G.edge(j,v))return G.edge(j,v);
        return 0;
    }
    bool end()const
	{
	    return(i>=G.V()&&j>=G.V());
	}
};

#endif