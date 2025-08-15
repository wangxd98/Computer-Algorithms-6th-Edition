#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "wbm.h"

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

int main()
{
    check();
    return 0;
}

