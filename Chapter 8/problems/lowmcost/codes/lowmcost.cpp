#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "lowerm.h"

int check()
{
	int n,m,s,t,se,x,y,caplow,cap,c;
    while(cin>>n>>m>>s>>t){
  	    s--,t--;
        GRAPH<EDGE> G(n,1);
		vector<int> sd(n,0);
        for(int i=0;i<m;i++){
  	        cin>>x>>y>>caplow>>cap>>c;
  	        x--,y--;
		    sd[y]+=caplow;sd[x]-=caplow;
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





