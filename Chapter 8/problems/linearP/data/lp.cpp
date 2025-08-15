#include <bits/stdc++.h>
using namespace std;
#include "simplex.h"

int main()
{
	int m,n,m1,m2,m3;
	double minmax,**a,value;
	make2dArray(a,300,300);
	while(cin>>minmax>>m>>n){
		cin>>m1>>m2>>m3;
		int n1=n+m3,n2=n+m1+m3;
        for(int i=0;i<=m+1;i++)
            for(int j=0;j<=n1;j++)a[i][j]=0.0;
        for(int i=m-m3+1,j=n+1;i<=m;i++,j++){
	        a[i][j]=-1.0;
            a[m+1][j]=-1.0;
        }
        // 输入约束系数和右端项
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                cin>>value;
                a[i][j]=value;
	        }
            cin>>value;
            a[i][0]=value;
        }
        // 输入目标函数系数
        for(int j=1;j<=n;j++){
            cin>>value;
            a[0][j]=value*minmax;
        }
        LinearProgram X(minmax,m,n,m1,m2,m3,a);
        X.solve();
    }
    delete2dArray(a,300);
    return 0;
}
