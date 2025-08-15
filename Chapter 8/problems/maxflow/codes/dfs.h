
#define Maxe 5205
#define INF 6553555
 
template <class Type>
struct Edge
{
	int to;
	Type cap;
	int rev;//反向边
};

template <class Type>
struct FlowG 
{
    int n,m;
    vector<Edge<Type>> G[Maxe];//边表，需要检查重复边
    bool vi[Maxe];//访问标记
    FlowG(int n,int m):n(n),m(m){init(n);}
    void init(int n){for(int i=0;i<=m;i++)G[i].clear();}
	void Add(int from,int to,Type cap)
    {
	    Edge<Type> e;
	    e.cap=cap;e.to=to;e.rev=G[to].size();
	    G[from].push_back(e);
	    e.to=from;e.cap=0;e.rev=G[from].size()-1;
	    G[to].push_back(e);
    }
	
	Type dfs(int v,int t,Type f)//增广路
    {
	    if (v==t)return f;
	    vi[v]=true;
	    for (int i=0;i<G[v].size();++i){
		    Edge<Type> &e=G[v][i];
		    if (!vi[e.to] && e.cap>0){
			    Type d=dfs(e.to,t,std::min(f,e.cap));
			    if (d>0){
				    e.cap-=d,G[e.to][e.rev].cap+=d;
				    return d;
			    }
		    }
	    }
	    return 0;
    }
	
	Type Maxflow(int s,int t)
    {
	    Type flow=0;
	    while(1){
		    memset(vi,0,sizeof(vi));
		    Type f=dfs(s,t,Type(INF));
		    if (f==0)return flow;
		    flow+=f;
	    }
    }
};
