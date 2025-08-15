#include <bits/stdc++.h>
using namespace std;
#include "simplex.h"

int capacity()
{
	int m,n;
	double v,**a;
	make2dArray(a,300,300);
    while(cin>>n){
        m=n*(n+1)/2;
        for(int i=0;i<=n+1;i++)
            for(int j=0;j<=m+n;j++)a[i][j]=0.0;
        for(int i=1;i<=n;i++)cin>>a[i][0];
		for(int i=0,k=1;i<n;i++)
	        for(int j=0;j<n-i;j++)
	            cin>>v,a[0][k++]=-v;
        for(int k=0;k<n;k++){
            int p=n-k,q=k*n-k*(k-1)/2;
	        for(int i=0;i<p;i++)
                for(int j=i;j<p;j++)
                    a[i+k+1][q+j+1]=1;
        }
        LinearProgram X(-1,n,m,0,0,n,a);
        X.solve();
	}
    delete2dArray(a,300);
    return 0;
}

int main()
{
	capacity();
	return 0;
}
