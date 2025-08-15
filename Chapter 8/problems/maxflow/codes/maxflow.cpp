#include <bits/stdc++.h>
using namespace std;
#include "GRAPH.h"
//#include "FordFulkerson.h"
#include "preflow.h"

int check()
{
    int n,m,s,t,x,y,z,maxflow;
    while(cin>>n>>m>>s>>t){
    	s--,t--;
        GRAPH<EDGE> G(n,1);
        maxflow=0;
        while(m--){
            cin>>x>>y>>z;
            x--,y--;
            G.insert(new EDGE(x,y,z));
        }
        MAXFLOW<GRAPH<EDGE>,EDGE>(G,s,t,maxflow);
        cout<<maxflow<<endl;
	}
    return 0;
}

int main()
{
    check();
    return 0;
}