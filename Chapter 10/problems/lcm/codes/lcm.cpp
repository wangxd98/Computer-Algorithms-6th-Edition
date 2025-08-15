#include <bits/stdc++.h>
using namespace std;
#include "gcd.h"

const int M=998244353;

ll lcmm(int a, int b)
{
	ll r=a/gcd(a,b);
	r=r*b%M;
	return r;
}

int main() 
{
	int x,y;
	while(cin>>x>>y){
		cout<<lcmm(x,y)<<endl;
	}
	return 0;
}

