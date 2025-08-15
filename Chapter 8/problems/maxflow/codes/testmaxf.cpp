#include <bits/stdc++.h>
using namespace std;
//#include "dfs.h"
//#include "Edmon.h"
#include "isap.h"
//#include "dinic.h"

#define LL long long

void chk()
{
    int n,m,s,t,x,y;
    LL z;
    while(cin>>n>>m>>s>>t){
    	FlowG<LL> G(n,m);
		while(m--){
            cin>>x>>y>>z;
            G.Add(x,y,z);
        }
        cout<<G.Maxflow(s,t)<<endl;
	}
}

int main()
{
	chk();
    return 0;
}