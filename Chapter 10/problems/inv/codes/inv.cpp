#include <bits/stdc++.h>
using namespace std;

void inv(int n,int x[])
{
	x[0]=0,x[1]=1;
	for (int i=2;i<n;i++)x[i]=(n-n/i)*x[n%i]%n;
}

int main() 
{
	int a,b,n,d,x[1005];
	while(cin>>n){
	    inv(n,x);
		for(int i=2;i<n;i++)cout<<x[i]<<endl;
	}
	return 0;
}


