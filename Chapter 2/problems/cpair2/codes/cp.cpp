#include <bits/stdc++.h>
using namespace std;
#include "ch02.h"

int main()
{
    PointX a,b,*X=new PointX[500];
    int n=0;
    float x,y,d;
    while(cin>>x>>y){
    	X[n].ID=n+1;
    	X[n].x=x;X[n++].y=y;
	}
    Cpair2(X,n,a,b,d);
    cout<<fixed<<setprecision(2);
    cout <<a.ID<<" "<<b.ID<<endl;
    cout<<d<<endl;
    delete []X;
    return 0;
}
