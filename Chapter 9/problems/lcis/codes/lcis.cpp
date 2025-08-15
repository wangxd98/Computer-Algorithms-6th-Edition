#include <bits/stdc++.h> 
using namespace std;
#include "lcis.h"

int main()
{
	while(cin>>n>>m){
		for(int i=0;i<n;i++)cin>>x[i];
		for(int i=0;i<m;i++)cin>>y[i];
        //cout<<lcis()<<endl;
        cout<<lcisn()<<endl;
	}
    return 0;
}

