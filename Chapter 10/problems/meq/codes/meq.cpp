#include <bits/stdc++.h> 
using namespace std;
#include "meq.h"

signed main() 
{
    int a,b,n,x;
	while(cin>>a>>b>>n){
		if(meq(a,b,n,x))cout<<x<<endl;
	}
	return 0;
}
