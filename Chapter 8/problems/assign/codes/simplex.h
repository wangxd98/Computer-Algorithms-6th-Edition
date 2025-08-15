#ifndef MINCOST_
#define MINCOST_
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
	const Graph &G;int s,t;int valid;
    vector<Edge *> st;vector<int> mark,phi;

    void upbound(int &cap,int &cost)
	{
        cap=0;cost=0;
		for(int i=0;i<G.V();i++)
			for(int j=0;j<G.V();j++){
				if(G.edge(i,j)&& cap<G.edge(i,j)->cap())cap=G.edge(i,j)->cap();
				if(G.edge(i,j)&& cost<G.edge(i,j)->cost())cost=G.edge(i,j)->cost();
			}
	}

    void dfsR(Edge *e,int w)
    {
	    int v=e->other(w);
	    st[v]=e;
	    mark[v]=1;mark[w]=1;
	    dfs(v);dfs(w);
	    mark.assign(G.V(),-1);
    }

    void dfs(int v)
    {
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
		    int w=e->other(v);
		    if(mark[w]==-1){st[w]=e;mark[w]=1;dfs(w);}
	   }
    }

    int ST(int v)const{
	    if(st[v]==0)return 0;
        else return st[v]->other(v);
    }

    int phiR(int v)
    {
        if(mark[v]==valid)return phi[v];
        phi[v]=phiR(ST(v))- st[v]->costRto(v);
        mark[v]=valid;
        return phi[v];
    }

    int lca(int v,int w)
    {
	    mark[v]=++valid;mark[w]=valid;
        while(v!=w){
            if(v!=t)v=ST(v);
            if(v!=t && mark[v]==valid)return v;
            mark[v]=valid;
            if(w!=t)w=ST(w);
            if(w!=t && mark[w]==valid)return w;
            mark[w]=valid;
        }
        return v;
    }

    bool onpath(int a,int b,int c)
    {
        for(int i=a;i!=c;i=ST(i))
            if(i==b)return true;
        return false;
    }
	
	void reverse(int u,int x)
    {
	    Edge *e=st[u];
        for(int i=ST(u);e->other(i)!= x;i=e->other(i))
	    {Edge *y=st[i];st[i]=e;e=y;} 
    }

    void update(Edge *w,Edge *y)
    {
	    if(w==y)return;
	    int u=y->w(),v=y->v(),x=w->w();
        if(x==t || st[x]!=w)x=w->v();
        int r=lca(u,v);
        if(onpath(u,x,r)){reverse(u,x);st[u]=y;return;}
        if(onpath(v,x,r)){reverse(v,x);st[v]=y;return;} 
    }

    int costR(Edge *e,int v)
    {
	    int R=e->cost()+ phi[e->w()]-phi[e->v()];
        return  e->from(v)? R : -R;
    }

    Edge *besteligible()
    {
	    Edge *x=0;
        for(int v=0,min=INT_MAX;v<G.V();v++){
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
                if(e->capRto(e->other(v))> 0)
                    if(e->capRto(v)== 0)
                        if(costR(e,v)< min)
				          {x=e;min=costR(e,v);} 
	    }
        return x;
    }

    Edge *augment(Edge *x)
    {
	    int v=full(x)?x->w():x->v();
	    int w=x->other(v);
	    int r=lca(v,w);
        int d=x->capRto(w);
        for(int u=w;u!=r;u=ST(u))
            if(st[u]->capRto(ST(u))< d)
                d=st[u]->capRto(ST(u));
        for(int u=v;u!=r;u=ST(u))
            if(st[u]->capRto(u)< d)
                d=st[u]->capRto(u);
	    x->addflowRto(w,d);Edge* e=x;
        for(int u=w;u!=r;u=ST(u)){
		    st[u]->addflowRto(ST(u),d);
            if(st[u]->capRto(ST(u))== 0)e=st[u];
	    }
        for(int u=v;u!=r;u=ST(u)){
		    st[u]->addflowRto(u,d);
            if(st[u]->capRto(u)== 0)e=st[u];
	    }
        return e;
    }

    void showtree()
	{
	    for(int i=0;i<G.V();i++)
		    if(st[i])cout<<"i="<<i<<" : st[i]->v()="<<st[i]->v()<<" st[i]->w()="<<st[i]->w()<<endl;
    }

    bool full(Edge *x)
    {
        return(x->capRto(x->w())==0);
    } 

    bool empty(Edge *x)
    {
        return(x->capRto(x->v())==0);
    } 

public:
    MINCOST(Graph &G,int s,int t): 
      G(G),s(s),t(t),st(G.V()+1),mark(G.V()+1,-1),phi(G.V()+1)
    {
        int m,c,ss=s;
        G.expand();
	    upbound(m,c);
	    m=m*G.V();
	    c=c*G.V();
        s=G.V()-1;
		Edge *z=new EDGE(s,t,SE,c);
        G.insert(z);
        G.insert(new EDGE(s,ss,SE,0));
        z->addflowRto(t,SE);
        dfsR(z,t);
        for(valid=1;;valid++ ){
            phi[t]=z->costRto(s);
		    mark[t]=valid;
            for(int v=0;v<G.V();v++)
			    if(v!=t)phi[v]=phiR(v);
            Edge *x=besteligible();
            int rcost=costR(x,x->v());
		    if(full(x)&& rcost<=0||empty(x)&& rcost>=0)break;
            update(augment(x),x);
        }
        G.remove(z);delete z;
    }
};

#endif
