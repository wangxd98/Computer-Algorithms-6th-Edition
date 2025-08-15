#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "slp.h"
#define INF 0x3f3f3f3f

int check()
{
	int n,m,s,t,x,y,c;
    while(cin>>m>>n){
  	    s=0,t=m+2;
        GRAPH<EDGE>G(t+1,1);
		vector<int>a(m+2,0);
		for(int i=1;i<=m;i++){
			cin>>a[i];
			G.insert(new EDGE(i+1,i,INF,0));
		}
        for(int i=1;i<=n;i++){
        	cin>>x>>y>>c;
        	G.insert(new EDGE(x,y+1,INF,c));//注意处理重复边的情况，存储费用较小的边
		} 
        for(int i=1;i<=m+1;i++){
            if(a[i]-a[i-1]>0)G.insert(new EDGE(s,i,a[i]-a[i-1],0));
            if(a[i]-a[i-1]<0)G.insert(new EDGE(i,t,a[i-1]-a[i],0));
        }
		ConsecLP<GRAPH<EDGE>,EDGE>(G,s,t);
	}
    return 0;  
}

int main()
{
    check();
    return 0;
}

