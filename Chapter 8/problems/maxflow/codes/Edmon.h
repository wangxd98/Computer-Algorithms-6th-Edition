//最大流 Edmonds Karp 算法
#define maxn 5205
#define INF 6553555

template <class Type>
struct Edge
{
	int from,to;
	Type cap,flow;
	Edge(int from,int to,int cap,int flow=0):from(from),to(to),cap(cap),flow(flow){}
};

template <class Type>
struct FlowG 
{
    int n,m;
    vector<Edge<Type>> edges; //边数的两倍
    vector<int> G[maxn];//边表，G[i][j]表示节点i的第j条边在e数组中的序号，要检测重复边
    Type a[maxn];        //起点到i的可改进量
    int p[maxn];        //最短路树上p的入弧编号

    FlowG(int n,int m):n(n),m(m){init(n);}
    
    void init(int n)
    {
        for(int i=0;i<n;i++)G[i].clear();
        edges.clear();
    }
    
    void Add(int from,int to,Type cap)
    {
        edges.push_back(Edge<Type>(from,to,cap));
        edges.push_back(Edge<Type>(to,from,0));//反向
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    
    Type Maxflow(int s,int t)//时间O(v*E*E)
    {
        Type flow=0;
        while(1){
            memset(a,0,sizeof(a));
            queue<int> q;
            q.push(s);
            a[s]=INF;
            while(!q.empty()){
                int x=q.front();
                q.pop();
                for(int i=0;i<G[x].size();i++){
                    Edge<Type>& e=edges[G[x][i]];
                    if(!a[e.to] && e.cap > e.flow){
                        p[e.to]=G[x][i];
                        a[e.to]=min(a[x],e.cap-e.flow);
                        q.push(e.to);
                    }
                }
                if(a[t])break;
            }
            if(!a[t])break;
            for(int u=t;u!=s;u=edges[p[u]].from){
                edges[p[u]].flow+=a[t];
                edges[p[u]^1].flow-=a[t];
            }
            flow+=a[t];
        }
        return flow;
    }
};
