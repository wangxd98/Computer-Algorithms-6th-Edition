#include <bits/stdc++.h>
using namespace std;

const int inf=2147483647;
const int N=5e4+9,M=6e5+9;
	
int n,s,t,tt;
int c[N],d[N],h[N],idx[N],w[M],x[M],z[M];

void init()
{
	tt=1;
	memset(h,0,sizeof(h));
	memset(c,0,sizeof(c));
	memset(x,0,sizeof(x));
	memset(w,0,sizeof(w));
	memset(z,0,sizeof(z));
	memset(idx,0,sizeof(idx));
}

inline void AddEdge(int u,int v,int f) 
{
    x[++tt]=h[u],h[u]=tt,w[tt]=v,z[tt]=f;
    x[++tt]=h[v],h[v]=tt,w[tt]=u,z[tt]=0;
}

inline int bfs(int s,int t,int n) 
{
    for(int i=1;i<=n;++i)
        d[i]=0,c[i]=h[i];
    queue<int> que;
    que.push(s),d[s]=1;
    while(!que.empty()) {
        int u=que.front();
        que.pop();
        for(int i=h[u];i;i=x[i])
            if(!d[w[i]] && z[i] && w[i]<=n)
                d[w[i]]=d[u]+1,que.push(w[i]);
    }
    return d[t];
}

inline int dfs(int u,int t,int flow) 
{
    if(u==t) return flow;
    int rest=flow;
    for(int i=c[u];i && rest;i=x[i]) {
        c[u]=i;
        if(d[w[i]]!=d[u]+1||!z[i])continue;
        int tmp=dfs(w[i],t,std::min(z[i],rest));
        z[i]-=tmp,z[i^1]+=tmp,rest-=tmp;
        if(!tmp)d[w[i]]=0;
    }
    return flow-rest;
}

int Maxflow(int s,int t,int n) 
{
    int flow=0,tmp=0;
    while(bfs(s,t,n))
        while(tmp=dfs(s,t,inf))
            flow+=tmp;
    return flow;
}

void chk()
{
    int n,m,s,t,u,v,l,r;
    while(cin>>n>>m>>s>>t){
    	init();
    	AddEdge(t,s,inf);
		while(m--){
		    cin>>u>>v>>l>>r;
            AddEdge(u,v,r-l),idx[u]-=l,idx[v]+=l;
        }
        int ss=n+1,tt=n+2,sum=0;
		for(int i=1;i<=n;++i)
            if(idx[i]<0)AddEdge(i,tt,-idx[i]);
        else AddEdge(ss,i,idx[i]),sum+=idx[i];
        int res=Maxflow(ss,tt,n+2);
		if(res!=sum)cout<<-1<<endl;
		else{ 
		    int r=z[3];
			z[2]=z[3]=0;
            cout<<r-Maxflow(t,s,n)<<endl;
	    }
    }
}

int main()
{
	chk();
    return 0;
}
