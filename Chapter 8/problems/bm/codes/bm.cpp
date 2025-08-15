#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "bm.h"

int check()
{
    int n,m,e,x,y;
    while(cin>>m>>n>>e){
        GRAPH<EDGE> G(n,1);
        for(int i=0;i<e;i++){
    	    cin>>x>>y;
		    if(x>y)swap(x,y);
		    if(x>=n)cout<<"input error "<<x<<" "<<y<<endl;
    	    x--,y--;
            G.insert(new EDGE(x,y,1));
        }
        BMATCHING<GRAPH<EDGE>,EDGE>(G,m);
	}
    return 0;       
}

int main()
{
    check();
    return 0;
}