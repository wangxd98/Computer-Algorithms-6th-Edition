#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
//#include "cycles.h"
//#include "cycles1.h"
//#include "cycles2.h"
#include "simplex.h"
//#include "shortest.h"
//#include "shortest1.h"
//#include "shortest2.h"

int check()
{
	int n,m,s,t,se,x,y,cap,c;
    while(cin>>n>>m>>s>>t>>se){
  	    s--,t--;
        GRAPH<EDGE> G(n+1,1);
        for(int i=0;i<m;i++){
  	        cin>>x>>y>>cap>>c;
  	        x--,y--;
	        G.insert(new EDGE(x,y,cap,c)); 	  
        }
        G.insert(new EDGE(n,s,se,0)); 
        s=n;
        MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
        cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
	}
    return 0;   
}

int main()
{
    check();
    return 0;
}

