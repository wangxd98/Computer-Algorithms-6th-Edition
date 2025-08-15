//ISAP 算法 (Improved Shortest Augment Path)
#define maxN 10001
#define maxM 40001
#define INF 0x3f3f3f3f

template <class Type>
struct Edge
{
	int to,next;
	Type cap,flow;
};

template <class Type>
struct FlowG 
{
	int n,tol;
	int head[maxN],Q[maxN],S[maxN],gap[maxN],dep[maxN],cur[maxN];
	Edge<Type> edge[maxM];//需要检测重复边
	
    FlowG(int n,int m):n(n){init();}
	
	void init()
	{
		tol=0;
		memset(head,-1,sizeof(head));
	}
	
	void Add(int u,int v,Type w,Type rw=0)
	{
		edge[tol].to=v;edge[tol].cap=w;edge[tol].flow=0;
		edge[tol].next=head[u];head[u]=tol++;
		edge[tol].to=u;edge[tol].cap=rw;edge[tol].flow=0;
		edge[tol].next=head[v];head[v]=tol++;
	}
	
	void BFS(int s,int t)
	{
		memset(dep,-1,sizeof(dep));
		memset(gap,0,sizeof(gap));
		gap[0]=1;
		int front=0,rear=0;
		dep[t]=0;
		Q[rear++]=t;
		while(front!=rear){
			int u=Q[front++];
			for(int i=head[u];i!=-1;i=edge[i].next){
				int v=edge[i].to;
				if(dep[v]!=-1)continue;
				Q[rear++]=v;
				dep[v]=dep[u]+1;
				gap[dep[v]]++;
			}
		}
	}

	Type Maxflow(int s,int t)
	{
		BFS(s,t);
		memcpy(cur,head,sizeof(head));
		int top=0,u=s;
		Type ans=0;
		while(dep[s]<n){
			if(u==t){
				Type Min=INF;
				int inser;
				for(int i=0;i<top;i++)
					if(Min>edge[S[i]].cap-edge[S[i]].flow){
						Min=edge[S[i]].cap-edge[S[i]].flow;
						inser=i;
					}
				for(int i=0;i<top;i++){
					edge[S[i]].flow+=Min;
					edge[S[i]^1].flow-=Min;
				}
				ans+=Min,top=inser,u=edge[S[top]^1].to;
				continue;
			}
			bool flag=false;
			int v;
			for(int i=cur[u];i!=-1;i=edge[i].next){
				v=edge[i].to;
				if(edge[i].cap-edge[i].flow&&dep[v]+1==dep[u]){
					flag=true;
					cur[u]=i;
					break;
				}
			}
			if(flag){
				S[top++]=cur[u];
				u=v;
				continue;
			}
			int Min=n;
			for(int i=head[u];i!=-1;i=edge[i].next)
			    if(edge[i].cap-edge[i].flow&&dep[edge[i].to]<Min){
				    Min=dep[edge[i].to];
				    cur[u]=i;
			    }
			gap[dep[u]]--;
			if(!gap[dep[u]])return ans;
			dep[u]=Min+1,gap[dep[u]]++;
			if(u!=s)
				u=edge[S[--top]^1].to;
		}
		return ans;
	}
};
