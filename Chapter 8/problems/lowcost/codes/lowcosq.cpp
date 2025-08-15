# include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;
const int maxv=1011,maxe=30011;

int du[maxv],cur[maxv],head[maxv],to[maxe],edge[maxe],nxt[maxe],tot;
ll dis[maxv],h[maxv],flow[maxe],cap[maxe];
bool vis[maxv];

struct node
{
	int v;ll w;
	node(int _v=0,ll _w=0):v(_v),w(_w){}
	bool operator<(const node &a)const{return w>a.w;}
};

priority_queue<node> Q;

void addE(int u,int v,int w,ll c)
{
	to[++tot]=v;
	edge[tot]=w;
	cap[tot]=c;
	nxt[tot]=head[u];
	head[u]=tot;
}

void add(int u,int v,int w,ll c){addE(u,v,w,c);addE(v,u,-w,0);}

bool shrt(int n,int s,int t)
{
	fill(dis+1,dis+n+1,INF);
	memset(vis+1,0,sizeof(bool)*n);
	dis[s]=0;Q.emplace(s,0);
	while(!Q.empty()){
		node t=Q.top();Q.pop();
		if(vis[t.v]) continue;
		int u=t.v;vis[u]=1;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];ll w=edge[i]+h[u]-h[v];
			if(cap[i]>flow[i] && dis[v]>dis[u]+w) dis[v]=dis[u]+w,Q.emplace(v,dis[v]);
		}
	}
	return dis[t]<INF;
}

ll dfs(int u,int t,ll minn)
{
	if(!minn || u==t) return minn;
	vis[u]=1;
	ll ans=0,f;
	for(int &i=cur[u];i;i=nxt[i]){
		int v=to[i];ll w=edge[i]+h[u]-h[v];
		if(dis[v]==dis[u]+w && !vis[v] && cap[i]>flow[i] && (f=dfs(v,t,min(minn,cap[i]-flow[i])))>0){
			flow[i]+=f;flow[i^1]-=f;
			ans+=f;minn-=f;
		}
		if(!minn) break;
	}
	return ans;
}

void MCMF(int n,int s,int t,ll &flow,ll &cost)
{
	while(shrt(n,s,t)){
		memset(vis+1,0,sizeof(bool)*n);
		memcpy(cur+1,head+1,sizeof(int)*n);
		ll f=dfs(s,t,INF);
		flow+=f;cost+=f*(dis[t]+h[t]-h[s]);
		for(int i=1;i<=n;i++)
			if(dis[i]<INF) h[i]+=dis[i];
	}
}

void init() 
{
	tot=1;
    memset(du,0,sizeof(du));	
    memset(cur,0,sizeof(cur));
    memset(head,0,sizeof(head));
    memset(to,0,sizeof(to));
    memset(edge,0,sizeof(edge));
    memset(nxt,0,sizeof(nxt));
    memset(dis,0,sizeof(dis));	
    memset(h,0,sizeof(h));
    memset(flow,0,sizeof(flow));
    memset(cap,0,sizeof(cap));
    memset(vis,0,sizeof(vis));
}

int main()
{
	int n,m,s,t,ss,tt,u,v,cplw,cp,w;
	ll sum=0,mxl=0,cost=0;
	while(cin>>n>>m>>s>>t){
	    sum=0,mxl=0,cost=0;
		ss=n+1;tt=ss+1;
		init();
	    for(int i=1;i<=m;i++){
		    cin>>u>>v>>cplw>>cp>>w;
			if(w>=0) du[v]+=cplw,du[u]-=cplw,add(u,v,w,cp-cplw),cost+=(ll)cplw*w;
			else du[v]+=cp,du[u]-=cp,add(v,u,-w,cp-cplw),cost+=(ll)cp*w;
	    }
	    for(int i=1;i<=n;i++)
		    if(du[i]>0) add(ss,i,0,du[i]),sum+=du[i];
		    else if(du[i]<0) add(i,tt,0,-du[i]);
	    add(t,s,0,INF);
	    MCMF(n+2,ss,tt,mxl,cost);
		if(mxl!=sum) cout<<-1<<endl;
	    else{
		    mxl=flow[tot-1];
	        flow[tot]=flow[tot-1]=cap[tot]=cap[tot-1]=0;
	        MCMF(n+2,s,t,mxl,cost);
	        cout<<mxl<<" "<<cost<<endl;
	    }
	}
	return 0;
}

