#include <bits/stdc++.h>
using namespace std;

#include "GRAPH.h"
#include "even.h"

int check()
{
	int p,q,n,s,t,u,v,caplow,cap;
	double x;
    while(cin>>p>>q){
	    s=p+q,t=s+1;
	    n=p+q+2;
	    vector<int> sd(n,0);	 
	    vector<double> row(p,0);
	    vector<double> column(q,0);
        GRAPH<EDGE> G(n,1);
		for(int i=0;i<p;i++)
		    for(int j=0;j<q;j++){
			   cin>>x;x*=0.5;
			   row[i]+=x,column[j]+=x;
			   u=i,v=p+j,caplow=floor(x),cap=ceil(x);
	           sd[v]+=caplow,sd[u]-=caplow;
	           G.insert(new EDGE(u,v,caplow,cap));
			}
		for(int i=0;i<p;i++){
		    u=s,v=i,caplow=floor(row[i]),cap=ceil(row[i]);
	        sd[v]+=caplow,sd[u]-=caplow;
	        G.insert(new EDGE(u,v,caplow,cap));
		}
		for(int j=0;j<q;j++){
		    u=p+j,v=t,caplow=floor(column[j]),cap=ceil(column[j]);
	        sd[v]+=caplow,sd[u]-=caplow;
	        G.insert(new EDGE(u,v,caplow,cap));
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

