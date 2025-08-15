#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "low.h"

int check()
{
	int n,m,s,t,x,y,caplow,cap,c=0;
    while(cin>>n>>m>>s>>t){
    	s--,t--;
    	vector<int> sd(n);
        GRAPH<EDGE> G(n,1);
        for(int i=0;i<m;i++){
    	    cin>>x>>y>>caplow>>cap;
    	    x--,y--;
            sd[y]+=caplow,sd[x]-=caplow;
			G.insert(new EDGE(x,y,cap,c,caplow));    	    
        }
        LOWER<GRAPH<EDGE>,EDGE>(G,s,t,sd);
	}
    return 0;       
}

int main()
{
    check();
    return 0;
}
