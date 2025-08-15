#ifndef GRAPH_
#define GRAPH_

class EDGE 
{
    int pv,pw,pcap,pcaplow,pflow,pflag,pcost;
public:
    EDGE(int v,int w,int cap):
           pv(v),pw(w),pcap(cap),pflow(0){}
    EDGE(int v,int w,int caplow,int cap):
        pv(v),pw(w),pcaplow(caplow),pcap(cap),pflow(0),pflag(0){}
    int v()const{return pv;}
    int w()const{return pw;}
    int cap()const{return pcap;}
    int caplow()const{return pcaplow;}
    int flow()const{return pflow;}
    bool from(int v)const {return pv==v;}
    void sublow(){pcap-=pcaplow;}
    void addlow(){pcap+=pcaplow;pflow+=pcaplow;pflag=1;}
    bool residual(int v)const 
    {return(pv==v && pcap-pflow>0 || pw==v && pflow>0 );} 
    int other(int v)const {return from(v)?pw:pv;} 
    int capRto(int v)const
    {return from(v)?pflow-pcaplow*pflag:pcap-pflow;}
    void addflowRto(int v,int d){pflow+=from(v)?-d:d;}
};

template <class Edge> class GRAPH
{
    int Vcnt,Ecnt;bool digraph;
    vector< vector<Edge *> >adj;
public:
    GRAPH(int V,bool digraph=false):
         adj(V),Vcnt(V),Ecnt(0),digraph(digraph)
    {
        for(int i=0;i<V;i++)
            adj[i].assign(V,0);
    }
    GRAPH(){}

    int V()const{return Vcnt;}
    int E()const{return Ecnt;}
    bool directed()const{return digraph;}
    void insert(Edge *e)
    {
	    int v=e->v(),w=e->w();
        if(adj[v][w]==0)Ecnt++;
        adj[v][w]=e;
        if(!digraph)adj[w][v]=e;
    } 
    bool exist(Edge *e){return adj[e->v()][e->w()]!=0;}
    void remove(Edge *e)
    {
	    int v=e->v(),w=e->w();
        if(adj[v][w]!=0)Ecnt--;
        adj[v][w]=0;
        if(!digraph)adj[w][v]=0;
    } 
    Edge* edge(int v,int w)const 
    {return adj[v][w];}

    void outflow()
    {
        for(int s=0;s<Vcnt;s++)
            for(int t=0;t<Vcnt;t++)
		        if(adj[s][t] && adj[s][t]->from(s)&& adj[s][t]->flow()>0)
			        cout<<s<<"->"<<t<<" "<<adj[s][t]->flow()<<endl;
    }

    void outf0()
    {
        for(int s=0;s<Vcnt;s++){
            for(int t=0;t<Vcnt;t++)
		        if(adj[s][t] && adj[s][t]->from(s))
			        cout<<2*adj[s][t]->flow()<<" ";;
        	cout<<endl;
		}
    }

    void outf()
    {
        for(int s=0;s<Vcnt;s++){
            for(int t=0;t<Vcnt;t++)
		        if(adj[s][t] && adj[s][t]->from(s))
			        cout<<adj[s][t]->flow()<<" ";
        	cout<<endl;
		}
    }

    void checksd(int s,int t,int &ss,int &dd)
    {
        ss=0;dd=0;
	    for(int i=0;i<Vcnt;i++){
            if(adj[s][i] && adj[s][i]->from(s)&& adj[s][i]->flow()>0 )
			    ss+=adj[s][i]->flow();
            if(adj[i][t] && adj[i][t]->from(i)&& adj[i][t]->flow()>0 )
			    dd+=adj[i][t]->flow();
	    }
    }
};

template <class Edge>
class adjIterator
{
    const GRAPH<Edge> &G;
    int i,j,v;
public:
    adjIterator(const GRAPH<Edge> &G,int v): 
        G(G),v(v),i(0),j(0){}
    Edge *beg()
    {
	    i=-1;j=-1;return nxt();
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
