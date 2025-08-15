//escape

#include <bits/stdc++.h> 
using namespace std; 

#include "GRAPH.h"
//#include "cycles1.h"
//#include "cycles2.h"
//#include "simplex.h"
#include "shortest1.h"
//#include "shortest2.h"

int n,m,f,s,t,x,y;
int dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};  

bool bd(int x,int y)  
{// 边界点 
    return (x==1||x==n||y==1||y==m);  
}  
  
bool gr(int x,int y)  
{// 网格点  
    return (x>=1 && x<=n && y>=1 && y<=m);  
}  
  
int v(int x,int y,int k)  
{// 图顶点  
    return (x-1)*m+y+k*(n*m);  
}  

bool succ(GRAPH<EDGE> &G)
{
    int sum=0;
    adjIterator<EDGE> A(G,s);
    for(EDGE* e=A.beg();!A.end();e=A.nxt())
        if(e->from(s)&&e->flow()>0)sum++;
    if(sum<f)return 0;
    else return 1;
}

int comp()
{
    while(cin>>n>>m>>f){
        s=0,t=v(n,m,1)+1;  
        GRAPH<EDGE> G(t+1,1);
        for(int i=1;i<=n;++i)  
            for(int j=1;j<=m;++j){  
                G.insert(new EDGE(v(i,j,0),v(i,j,1),1,0));//网格边;
                int w=v(i,j,1);  
                if(bd(i,j))G.insert(new EDGE(w,t,1,0));//边界点 
                for(int k=0;k<4;++k){  
                    int x=i+dx[k],y=j+dy[k];//相邻边  
                    if(gr(x,y))G.insert(new EDGE(w,v(x,y,0),1,1));
                }  
            }  
        for(int i=1;i<=f;++i){  
			cin>>x>>y;  
            G.insert(new EDGE(s,v(x,y,0),1,0));//初始点 
        }  
        MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
        if(succ(G))cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
        else cout<<-1<<endl;
    }        
    return 0;   
}

int main()
{
    comp();
    return 0;
}

