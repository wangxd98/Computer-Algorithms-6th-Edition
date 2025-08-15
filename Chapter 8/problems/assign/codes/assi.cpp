#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "assi.h"

int check()
{
	int n,m,x,y,c;
    while(cin>>n>>m){
        GRAPH<EDGE> G(2*n,1);
        for(int i=0;i<m;i++){
  	        cin>>x>>y>>c;
			x--,y--;
	        G.insert(new EDGE(x,y+n,1,c));
        }
		ASSIGNMENT<GRAPH<EDGE>,EDGE>H(G);
	}
    return 0;  
}

int chk()
{
	int n,m,s,t,x,y,c;
    while(cin>>n>>m){
    	s=2*n,t=s+1;
        GRAPH<EDGE> G(s+2,1);
        for(int i=0;i<m;i++){
  	        cin>>x>>y>>c;
			x--,y--;
	        G.insert(new EDGE(x,y+n,1,c));
	        G.insert(new EDGE(s,x,1,0));
	        G.insert(new EDGE(y+n,t,1,0));
        }
		MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
        int maxf=0;
        adjIterator<EDGE> A(G,s);
        for(EDGE* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxf+=e->flow();
        if(maxf<n)cout<<-1<<endl;
        else cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
	}
    return 0;  
}

int main()
{
    check();
    //chk();
    return 0;
}

