#include <bits/stdc++.h>
using namespace std;

int exgcd(int a,int b,int &x,int &y) 
{
    int c=y=0,d=x=1;
    while (b){
        int q=a/b,t=a;
        a=b;b=t%b;
        t=x;x=c;c=t-q*c;
        t=y;y=d;d=t-q*d;
    }
    return a;
}

int meq(int a, int b, int n, int &x)
{
	int v;
    int d=exgcd(a,n,x,v);
    if (b%d) return 0;
    n/=d,x=((x*b/d)%n+n)%n;
	return d;
}

int main() 
{
	int a,b,n,d,x;
	while(cin>>a>>b>>n){
		d=meq(a,b,n,x);
		if(d)cout<<d<<" "<<x<<endl;
		else cout<<"-1";
	}
	return 0;
}


