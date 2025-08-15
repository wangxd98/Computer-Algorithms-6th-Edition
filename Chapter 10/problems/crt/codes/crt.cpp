#include <bits/stdc++.h>
using namespace std;

int exgcd(int a,int b,int &x,int &y)
{
    int c=y=0,d=x=1;
    while(b){
        int q=a/b,t=a;
        a=b;b=t%b;
        t=x;x=c;c=t-q*c;
        t=y;y=d;d=t-q*d;
    }
    return a;
}

int crt(int k,int a[],int m[])
{
    int x,y,ni,r=0,n=1;
    for(int i=0;i<k;i++)n*=m[i];
    for(int i=0;i<k;i++){
        ni=n/m[i];
        exgcd(ni,m[i],x,y);
        r=(r+ni*x*a[i])%n;
    }
    return(r+n)%n;
}

int main()
{
    int k,a[100],m[100];
    while(cin>>k){
	    for(int i=0;i<k;i++)cin>>a[i]>>m[i];
        cout<<crt(k,a,m)<<endl;
 	}
	return 0;
}


