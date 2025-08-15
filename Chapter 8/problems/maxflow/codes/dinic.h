//Dinic 算法
#define maxN 10001
#define maxM 40001
#define INF 0x3f3f3f3f

template <class Type>
struct Edge
{
	int u,v,nxt;
	Type cap;
	Edge(int u,int v,Type cap,int nxt):u(u),v(v),cap(cap),nxt(nxt){}
	Edge(){}
};

template <class Type>
struct FlowG 
{
	int head[maxN],dis[maxN],vis[maxN];
	Edge<Type> E[maxM];
	int n,tol;
	
	FlowG(int n,int m):n(n){init();}

	void init()
	{
		tol=0;
		memset(head,-1,sizeof(head));
	}
	void Add(int u,int v,Type cap)
	{
		E[tol]=Edge<Type>(u,v,cap,head[u]);//正向边
		head[u]=tol++;
		E[tol]=Edge<Type>(v,u,0,head[v]);//反向边容量为0
		head[v]=tol++;
	}
	bool BFS(int s,int t)
	{
		queue<int> q;
		q.push(s);
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=head[x];~i;i=E[i].nxt){
				if(E[i].cap>0&&dis[E[i].v]==INF){
					dis[E[i].v]=dis[x]+1;
					if(E[i].v==t)return true;
					q.push(E[i].v);
				}
			}
		}
		return dis[t]<INF; //能否到达汇点
	}
	Type dfs(int x,Type maxf,int t)
	{
		if(x==t||maxf<=0)return maxf;
		//i=vis[x]当前弧优化
		int ret=0;
		for(int &i=vis[x];~i;i=E[i].nxt){
			if(dis[E[i].v]==dis[x]+1&&E[i].cap>0){
				Type flow=dfs(E[i].v,min(maxf,E[i].cap),t);
				if(flow){
					ret+=flow,maxf-=flow;
					E[i].cap-=flow;//减少正向边流量
					E[i^1].cap+=flow; //增加反向边流量
				}
				if(maxf==0)break;
			}
		}
		return ret;//找不到增广路
	}
	
	Type Maxflow(int s,int t)
	{
		Type ans=0;
		while(BFS(s,t)){//建立分层图
			Type flow;
			for(int i=1;i<=n;i++)//初始化vis，注意标号从0开始时要修改
				vis[i]=head[i];
			while(flow=dfs(s,INF,t))//一次BFS可多次增广
				ans+=flow;
		}
		return ans;
	}
};
